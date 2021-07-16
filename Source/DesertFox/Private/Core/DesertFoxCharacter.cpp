// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/DesertFoxCharacter.h"
#include "Core/DesertFoxMovementComponent.h"
#include "Core/DesertFoxPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TimelineComponent.h"

void BindTimelineComponent(UObject* BindingObject, UCurveFloat* CurveData, UTimelineComponent* Component, const FName& BindFunctionName)
{
	if (IsValid(BindingObject) && Component && CurveData)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(BindingObject, BindFunctionName);

		Component->AddInterpFloat(CurveData, TimelineProgress);
		Component->SetLooping(false);
		Component->SetPlaybackPosition(0.f, false);
		Component->RegisterComponent();
	}
}

ADesertFoxCharacter::ADesertFoxCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDesertFoxMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 270.0f, 0.0f);
		GetCharacterMovement()->JumpZVelocity = 600.f;
		GetCharacterMovement()->AirControl = 0.0f;
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	if (CameraBoom)
	{
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 300.0f;
		CameraBoom->bUsePawnControlRotation = true;
	}

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	if (FollowCamera)
	{
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->bUsePawnControlRotation = false;
	}
}

void ADesertFoxCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (LeftLookCurve)
	{
		LeftLookTimelineComponent = NewObject<UTimelineComponent>(this, FName("LeftLookTimelineAnimation"));
		BindTimelineComponent(this, LeftLookCurve, LeftLookTimelineComponent, FName("LeftLookHandleProgress"));
	}

	if (RightLookCurve)
	{
		RightLookTimelineComponent = NewObject<UTimelineComponent>(this, FName("RightLookTimelineAnimation"));
		BindTimelineComponent(this, RightLookCurve, RightLookTimelineComponent, FName("RightLookHandleProgress"));
	}
}

void ADesertFoxCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (LeftLookTimelineComponent)
	{
		LeftLookTimelineComponent->TickComponent(DeltaSeconds, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (RightLookTimelineComponent)
	{
		RightLookTimelineComponent->TickComponent(DeltaSeconds, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	// X is left look value, Y is right look value
	CurrentLookDegree = (-LookAmount.X + LookAmount.Y) * 180.0f;
}

void ADesertFoxCharacter::Run()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->CanRun())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::Running);
		}
	}
}

void ADesertFoxCharacter::Walk()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->CanWalk())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::Walking);
		}
	}
}

void ADesertFoxCharacter::SlowWalk()
{
	UDesertFoxMovementComponent* DesertFoxMovement= Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->CanSlowWalk())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::SlowWalking);
		}
	}
}

void ADesertFoxCharacter::RestoreMovementState()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		DesertFoxMovement->RestoreMovmenetState();
	}
}

void ADesertFoxCharacter::StartJump()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->CanJump())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::Jumping);

			if (CanReadyToJump())
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADesertFoxCharacter::RealJump, ReadyToJumpTime.GetValue(), false);
			}
			else
			{
				RealJump();
			}
		}
	}
}

void ADesertFoxCharacter::RealJump()
{
	Jump();
}

bool ADesertFoxCharacter::CanReadyToJump() const
{
	return ReadyToJumpTime.IsSet();
}

void ADesertFoxCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);


	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		DesertFoxMovement->SetMovementState(EDesertFoxMovementState::Idle, false);
		DesertFoxMovement->RestoreMovmenetState();
	}
}

void ADesertFoxCharacter::LeftLookHandleProgress(float InterpValue)
{
	LookAmount.X = InterpValue;
}

void ADesertFoxCharacter::RightLookHandleProgress(float InterpValue)
{
	LookAmount.Y = InterpValue;
}

void ADesertFoxCharacter::StartLookLeft()
{
	if (LeftLookTimelineComponent)
	{
		float NewPlayRate = LookPlayRate.X;
		if (RightLookTimelineComponent && RightLookTimelineComponent->IsPlaying())
		{
			NewPlayRate = OppositionLookPlayRate.X;
		}

		LeftLookTimelineComponent->SetPlayRate(NewPlayRate);
		LeftLookTimelineComponent->Play();
	}
}

void ADesertFoxCharacter::StopLookLeft()
{
	if (LeftLookTimelineComponent)
	{
		float NewPlayRate = LookPlayRate.Y;
		if (RightLookTimelineComponent && RightLookTimelineComponent->IsPlaying())
		{
			NewPlayRate = OppositionLookPlayRate.Y;
		}

		LeftLookTimelineComponent->SetPlayRate(NewPlayRate);
		LeftLookTimelineComponent->Reverse();
	}
}

void ADesertFoxCharacter::StartLookRight()
{
	if (RightLookTimelineComponent)
	{
		float NewPlayRate = LookPlayRate.X;
		if (LeftLookTimelineComponent && LeftLookTimelineComponent->IsPlaying())
		{
			NewPlayRate = OppositionLookPlayRate.X;
		}

		RightLookTimelineComponent->SetPlayRate(NewPlayRate);
		RightLookTimelineComponent->Play();
	}
}

void ADesertFoxCharacter::StopLookRight()
{
	if (RightLookTimelineComponent)
	{
		float NewPlayRate = LookPlayRate.Y;
		if (LeftLookTimelineComponent && LeftLookTimelineComponent->IsPlaying())
		{
			NewPlayRate = OppositionLookPlayRate.Y;
		}

		RightLookTimelineComponent->SetPlayRate(NewPlayRate);
		RightLookTimelineComponent->Reverse();
	}
}