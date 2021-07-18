// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

void FMovemenetStateInfo::Set(UWIDMovementComponent* OtherMovement) const
{
	if (OtherMovement)
	{
		if (bOrientRotationToMovement.IsSet())
			OtherMovement->bOrientRotationToMovement = bOrientRotationToMovement.GetValue();
		if (RotationRate.IsSet())
			OtherMovement->RotationRate = RotationRate.GetValue();
		if (JumpZVelocity.IsSet())
			OtherMovement->JumpZVelocity = JumpZVelocity.GetValue();
		if (Speed.IsSet())
			OtherMovement->MaxWalkSpeed = Speed.GetValue();
	}
}

void UWIDMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SetMovementState(EWIDMovementState::Idle);
}

void UWIDMovementComponent::SetMovementState(const EWIDMovementState NewMovmenetState, bool bSaveMovement)
{
	if (CurrentMovementState == NewMovmenetState)
		return;

	if (bSaveMovement)
	{
		SaveMovementState(CurrentMovementState);
	}
	
	const FMovemenetStateInfo* const MovementStateInfo = MovementStateInfoMap.Find(NewMovmenetState);
	if (MovementStateInfo)
	{
		MovementStateInfo->Set(this);
	}

	CurrentMovementState = NewMovmenetState;
}

void UWIDMovementComponent::SaveMovementState(const EWIDMovementState OldMovmenetState)
{
	// Do not save while jumping
	if (OldMovmenetState == EWIDMovementState::Jumping || OldMovmenetState == EWIDMovementState::None)
		return;

	LastMovementState = OldMovmenetState;
}

void UWIDMovementComponent::RestoreMovmenetState()
{
	// Do not restore while jumping
	if (IsJumping())
		return;

	if (LastMovementState == EWIDMovementState::None)
	{
		LastMovementState = EWIDMovementState::Idle;
	}

	if (IsValid(CharacterOwner))
	{
		APlayerController* PlayerController = CharacterOwner->GetController<APlayerController>();
		if (IsValid(PlayerController))
		{
			// When returning from a special state, return to the idle state unless the corresponding key is pressed
			if ((LastMovementState == EWIDMovementState::Running) && !PlayerController->IsInputKeyDown(EKeys::LeftShift))
				LastMovementState = EWIDMovementState::Idle;
			if ((LastMovementState == EWIDMovementState::SlowWalking) && !PlayerController->IsInputKeyDown(EKeys::LeftControl))
				LastMovementState = EWIDMovementState::Idle;
		}
	}

	SetMovementState(LastMovementState);
}

void UWIDMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{
	if (IsValid(CharacterOwner) && IsFalling())
	{
		FHitResult HitResult(ForceInit);

		FVector CapsuleHalfHeight = FVector(0.0f, 0.0f, CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		FVector StartLoc = CharacterOwner->GetActorLocation() - CapsuleHalfHeight;
		FVector EndLoc = StartLoc + (FVector::DownVector * 10000.0f);

		if (CharacterOwner->GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
		{
			DistanceToFloorWhileFalling = HitResult.Distance;
		}
	}

	Super::PhysFalling(deltaTime, Iterations);
}

bool UWIDMovementComponent::CanRun() const
{
	return IsWalking() && CurrentMovementState != EWIDMovementState::Jumping;
}

bool UWIDMovementComponent::CanWalk() const
{
	return IsWalking() && CurrentMovementState != EWIDMovementState::Jumping;
}

bool UWIDMovementComponent::CanSlowWalk() const
{
	return IsWalking() && CurrentMovementState != EWIDMovementState::Jumping;
}

bool UWIDMovementComponent::CanJump() const
{
	return IsWalking() && CurrentMovementState != EWIDMovementState::Jumping;
}