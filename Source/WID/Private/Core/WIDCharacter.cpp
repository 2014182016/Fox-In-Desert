// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "Core/WIDPlayerController.h"
#include "Core/WIDPlayerState.h"
#include "Core/WIDGameUserSettings.h"
#include "Animation/WIDAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

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

	FrontBodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("FrontBodyCollision"));
	if (FrontBodyCollision)
	{
		FrontBodyCollision->SetupAttachment(GetMesh(), USpringArmComponent::SocketName);
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

	// Apply stored TargetArmLength
	UWIDGameUserSettings* WIDGameUserSettings = Cast<UWIDGameUserSettings>(GEngine->GetGameUserSettings());
	if (WIDGameUserSettings && CameraBoom)
	{
		CameraBoom->TargetArmLength = WIDGameUserSettings->ZoomDistance;
	}

	LastMoveStamp = 0.0f;
	bCanJump = true;
}

void AWIDCharacter::Destroyed()
{
	Super::Destroyed();

	// Save last TargetArmLength
	UWIDGameUserSettings* WIDGameUserSettings = Cast<UWIDGameUserSettings>(GEngine->GetGameUserSettings());
	if (WIDGameUserSettings && CameraBoom)
	{
		WIDGameUserSettings->ZoomDistance = CameraBoom->TargetArmLength;
	}
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
	
	UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
	if (WIDMovement->IsWalking() && WIDMovement->MovementMode == MOVE_Walking)
	{
		if (bTiltBody)
		{
			CheckTiltBody(DeltaSeconds);
		}

		// Use foot ik only when character standing still
		if (bUseFootIK && GetVelocity().IsNearlyZero())
		{
			CheckFootPlacement(DeltaSeconds);
		}
	}
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
	AWIDPlayerState* WIDPlayerState = GetPlayerState<AWIDPlayerState>();
	if (IsValid(WIDPlayerState) && !WIDPlayerState->IsExhausted())
	{
		UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(GetCharacterMovement());
		if (WIDMovement)
		{
			if (WIDMovement->CanJump() && bCanJump)
			{
				bCanJump = false;
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

				WIDPlayerState->ConsumeJumpingStamina();
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

	if (DelayActivateJump > 0.0f)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWIDCharacter::EnableJump, DelayActivateJump, false);
	}
	else
	{
		EnableJump();
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

void AWIDCharacter::EnableJump()
{
	bCanJump = true;
}

FVector AWIDCharacter::CheckAcceptableNormal(const FVector& InNormal) const
{
	// If the angle between the Z-axis and normal is less than a certain value, apply character ratotion
	const float DegreeFromNormal = FMath::RadiansToDegrees(acosf(FVector::DotProduct(FVector::ZAxisVector, InNormal)));
	if (DegreeFromNormal < CharacterRotationMaxDegree)
	{
		return InNormal;
	}
	return FVector::ZeroVector;
}

void AWIDCharacter::CheckTiltBody(float DeltaTime)
{
	if (GetMesh())
	{
		FVector HitNormal[2];

		{
			FHitResult HitResult(ForceInit);

			FVector StartLoc = GetActorLocation();
			FVector EndLoc = StartLoc + (FVector::DownVector * WID::CheckWalkingDistance);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
			{
				HitNormal[0] = CheckAcceptableNormal(HitResult.ImpactNormal);
			}
		}

		{
			FHitResult HitResult(ForceInit);

			FVector StartLoc = FrontBodyCollision->GetComponentLocation();
			FVector EndLoc = StartLoc + (FVector::DownVector * WID::CheckWalkingDistance);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
			{
				HitNormal[1] = CheckAcceptableNormal(HitResult.ImpactNormal);
			}
		}

		const FVector AverageNormal = CheckAcceptableNormal((HitNormal[0] + HitNormal[1]) * 0.5f);
		if (!AverageNormal.IsZero())
		{
			FRotator OldRotation = GetMesh()->GetRelativeRotation();

			// Find the rotation angle of normal
			const float NewYaw = OldRotation.Yaw;
			const float NewPitch = UKismetMathLibrary::MakeRotFromYZ(GetMesh()->GetRightVector(), AverageNormal).Pitch;
			const float NewRoll = UKismetMathLibrary::MakeRotFromXZ(GetMesh()->GetForwardVector(), AverageNormal).Roll;
			FRotator NewRotation = FRotator(NewPitch, NewYaw, NewRoll);

			// Apply the new rotation interpolated
			NewRotation = UKismetMathLibrary::RInterpTo(OldRotation, NewRotation, DeltaTime, StandingRotationInterpSpeed);
			GetMesh()->SetRelativeRotation(NewRotation);
		}
	}
}

void AWIDCharacter::CheckFootPlacement(float DeltaTime)
{
	if (GetMesh())
	{
		FVector2D HitLocationZ = FVector2D(0.0f, 0.0f);

		// Inspect the floor on each foot
		for (EFootPosition FootPosition : TEnumRange<EFootPosition>())
		{
			const int32 CurrentIndex = static_cast<int32>(FootPosition);
			const FName FootBoneName = WID::GetFootBoneName(FootPosition);
			if (FootBoneName != FName("Root"))
			{
				const FVector BoneLocation = GetMesh()->GetBoneLocation(FootBoneName);

				FHitResult HitResult(ForceInit);
				FVector StartLoc = BoneLocation;
				StartLoc.Z = GetActorLocation().Z;

				const float CheckFootDistance = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + WID::CheckFootIKDistance;
				FVector EndLoc = StartLoc + (FVector::DownVector * CheckFootDistance);

				if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
				{
					// Cache offset z values where feet is located
					const float DiffFootLocationZ = GetActorLocation().Z - HitResult.Location.Z;
					FootIKLocations[CurrentIndex].X = UKismetMathLibrary::FInterpTo(FootIKLocations[CurrentIndex].X, DiffFootLocationZ, DeltaTime, IKPositionIterpSpeed);

					// Cache without comparison if the value is set to zero
					if (HitLocationZ.IsZero())
					{
						HitLocationZ.X = HitResult.Location.Z;
						HitLocationZ.Y = HitResult.Location.Z;
					}
					// Cache the min max value of the z value to calculate the hip offset
					else
					{
						HitLocationZ.X = FMath::Min<float>(HitLocationZ.X, HitResult.Location.Z);
						HitLocationZ.Y = FMath::Max<float>(HitLocationZ.Y, HitResult.Location.Z);
					}
					continue;
;				}
			}

			// If the data di not fit or collide, set to zero
			FootIKLocations[CurrentIndex] = FVector::ZeroVector;
		}

		// Calculate the location for positioning the hip as the average of the difference between z values
		const float DiffHipLocationZ = FMath::Min<float>(FMath::Abs<float>(HitLocationZ.X - HitLocationZ.Y), WID::MinHipIKOffsetZ);
		const float NewHipOffsetZ = DiffHipLocationZ * -0.5f;
		HipIKOffset.Z = UKismetMathLibrary::FInterpTo(HipIKOffset.Z, NewHipOffsetZ, DeltaTime, IKPositionIterpSpeed);
	}
}