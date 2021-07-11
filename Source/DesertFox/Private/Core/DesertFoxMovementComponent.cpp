// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DesertFoxMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

void FMovemenetStateInfo::Set(class UDesertFoxMovementComponent* const OtherMovement) const
{
	if (OtherMovement)
	{
		if (bOrientRotationToMovement.IsSet())
			OtherMovement->bOrientRotationToMovement = bOrientRotationToMovement.GetValue();
		if (RotationRate.IsSet())
			OtherMovement->RotationRate = RotationRate.GetValue();
		if (JumpZVelocity.IsSet())
			OtherMovement->JumpZVelocity = JumpZVelocity.GetValue();
	}
}

void UDesertFoxMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SetMovementState(EDesertFoxMovementState::Idle);
}

void UDesertFoxMovementComponent::SetMovementState(const EDesertFoxMovementState NewMovmenetState, bool bSaveMovement)
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

float UDesertFoxMovementComponent::GetMaxSpeed() const
{
	switch (CurrentMovementState)
	{
	case EDesertFoxMovementState::Idle:
	case EDesertFoxMovementState::Walking:
		return MaxWalkSpeed;
	case EDesertFoxMovementState::Running:
		return MaxRunSpeed;
	case EDesertFoxMovementState::SlowWalking:
		return MaxSlowWalkSpeed;
	case EDesertFoxMovementState::Jumping:
		return LastMaxSpeed;
	}
	return 0.0f;
}

void UDesertFoxMovementComponent::SaveMovementState(const EDesertFoxMovementState OldMovmenetState)
{
	// Do not save while jumping
	if (OldMovmenetState == EDesertFoxMovementState::Jumping || OldMovmenetState == EDesertFoxMovementState::None)
		return;

	LastMovementState = OldMovmenetState;
	LastMaxSpeed = GetMaxSpeed();
}

void UDesertFoxMovementComponent::RestoreMovmenetState()
{
	// Do not restore while jumping
	if (IsJumping())
		return;

	if (LastMovementState == EDesertFoxMovementState::None)
	{
		LastMovementState = EDesertFoxMovementState::Idle;
	}

	if (IsValid(CharacterOwner))
	{
		APlayerController* PlayerController = CharacterOwner->GetController<APlayerController>();
		if (IsValid(PlayerController))
		{
			// When returning from a special state, return to the idle state unless the corresponding key is pressed
			if ((LastMovementState == EDesertFoxMovementState::Running) && !PlayerController->IsInputKeyDown(EKeys::LeftShift))
				LastMovementState = EDesertFoxMovementState::Idle;
			if ((LastMovementState == EDesertFoxMovementState::SlowWalking) && !PlayerController->IsInputKeyDown(EKeys::LeftControl))
				LastMovementState = EDesertFoxMovementState::Idle;
		}
	}

	SetMovementState(LastMovementState);
}

void UDesertFoxMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
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

bool UDesertFoxMovementComponent::CanRun() const
{
	return IsWalking() && CurrentMovementState != EDesertFoxMovementState::Jumping;
}

bool UDesertFoxMovementComponent::CanSlowWalk() const
{
	return IsWalking() && CurrentMovementState != EDesertFoxMovementState::Jumping;
}

bool UDesertFoxMovementComponent::CanJump() const
{
	return IsWalking() && CurrentMovementState != EDesertFoxMovementState::Jumping;
}