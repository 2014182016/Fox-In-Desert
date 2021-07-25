// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WIDAnimInstance.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "Curves/CurveFloat.h"

void UWIDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	DefaultJumpAnimStartPosition = JumpAnimStartPosition;
}

void UWIDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AWIDCharacter* WIDCharacter = Cast<AWIDCharacter>(TryGetPawnOwner());
	if (IsValid(WIDCharacter))
	{
		CurrentSpeed = WIDCharacter->GetVelocity().Size();
		CurrentSpeed2D = WIDCharacter->GetVelocity().Size2D();

		JumpAnimStartPosition = WIDCharacter->CanReadyToJump() ? 0.0f : DefaultJumpAnimStartPosition;
		CurrentLookDegree = WIDCharacter->CurrentLookDegree * LookAnimRate;

		UWIDMovementComponent* WIDMovement = Cast<UWIDMovementComponent>(WIDCharacter->GetCharacterMovement());
		if (WIDMovement)
		{
			bIsInAir = WIDMovement->IsFalling();
			bIsSlowWalking = WIDMovement->IsSlowWalking();
			bIsJumping = WIDMovement->IsJumping();

			if (JumpAnimRateCurve)
			{
				JumpAnimRate = JumpAnimRateCurve->GetFloatValue(WIDMovement->DistanceToFloorWhileFalling);
			}
		}
	}
}

void UWIDAnimInstance::PlayDeathAnimation()
{
	bDied = true;

	// Check the maximum number of death animation specified in the animation blueprint
	DeathAnimationIndex = FMath::RandRange(0, 4);
}
