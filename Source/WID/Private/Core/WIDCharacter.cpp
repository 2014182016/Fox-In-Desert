// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "Core/WIDPlayerController.h"
#include "Core/WIDPlayerState.h"
#include "Animation/WIDAnimInstance.h"
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

AWIDCharacter::AWIDCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWIDMovementComponent>(ACharacter::CharacterMovementComponentName))
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

void AWIDCharacter::BeginPlay()
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

	LastMoveStamp = 0.0f;
}

void AWIDCharacter::Tick(float DeltaSeconds)
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

void AWIDCharacter::Run()
{
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		if (WIDMovement->CanRun())
		{
			WIDMovement->SetMovementState(EWIDMovementState::Running);
		}
	}
}

void AWIDCharacter::Walk()
{
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		if (WIDMovement->CanWalk())
		{
			WIDMovement->SetMovementState(EWIDMovementState::Walking);
		}
	}
}

void AWIDCharacter::SlowWalk()
{
	UWIDMovementComponent* WIDMovement= Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		if (WIDMovement->CanSlowWalk())
		{
			WIDMovement->SetMovementState(EWIDMovementState::SlowWalking);
		}
	}
}

void AWIDCharacter::RestoreMovementState()
{
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		WIDMovement->RestoreMovmenetState();
	}
}

void AWIDCharacter::StartJump()
{
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		if (WIDMovement->CanJump())
		{
			WIDMovement->SetMovementState(EWIDMovementState::Jumping);

			if (CanReadyToJump())
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWIDCharacter::RealJump, ReadyToJumpTime.GetValue(), false);
			}
			else
			{
				RealJump();
			}
		}
	}
}

void AWIDCharacter::RealJump()
{
	Jump();
}

bool AWIDCharacter::CanReadyToJump() const
{
	return ReadyToJumpTime.IsSet();
}

void AWIDCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		WIDMovement->SetMovementState(EWIDMovementState::Idle, false);
		WIDMovement->RestoreMovmenetState();
	}
}

void AWIDCharacter::LeftLookHandleProgress(float InterpValue)
{
	LookAmount.X = InterpValue;
}

void AWIDCharacter::RightLookHandleProgress(float InterpValue)
{
	LookAmount.Y = InterpValue;
}

void AWIDCharacter::StartLookLeft()
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

void AWIDCharacter::StopLookLeft()
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

void AWIDCharacter::StartLookRight()
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

void AWIDCharacter::StopLookRight()
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

float AWIDCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDied)
		return 0.0f;

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AWIDPlayerState* WIDPlayerState = GetPlayerState<AWIDPlayerState>();
	if (IsValid(WIDPlayerState))
	{
		WIDPlayerState->AddHealth(-DamageAmount);
	}

	return ActualDamage;
}

void AWIDCharacter::NotifyDied()
{
	bDied = true;

	if (GetMesh())
	{
		UWIDAnimInstance* WIDAnimInstance = Cast<UWIDAnimInstance>(GetMesh()->GetAnimInstance());
		if (WIDAnimInstance)
		{
			WIDAnimInstance->PlayDeathAnimation();
		}
	}
}

void AWIDCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);

	LastMoveStamp = GetWorld()->GetTimeSeconds();
}

void AWIDCharacter::Sleep()
{
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		WIDMovement->SetMovementState(EWIDMovementState::Sleeping, false);
	}
}

void AWIDCharacter::WakeUp()
{
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement)
	{
		WIDMovement->SetMovementState(EWIDMovementState::Idle, false);
	}
}