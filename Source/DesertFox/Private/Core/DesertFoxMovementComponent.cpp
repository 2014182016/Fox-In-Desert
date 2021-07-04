// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DesertFoxMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

void UDesertFoxMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SetMovementState(EDesertFoxMovementState::Idle);
}

void UDesertFoxMovementComponent::SetMovementState(const EDesertFoxMovementState NewMovmenetState)
{
	if (CurrentMovementState == NewMovmenetState)
		return;

	SaveMovementState(CurrentMovementState);

	switch (NewMovmenetState)
	{
	case EDesertFoxMovementState::Idle:
	case EDesertFoxMovementState::Walking:
	case EDesertFoxMovementState::Running:
	case EDesertFoxMovementState::SlowWalking:
	{
		FMovemenetStateInfo const* const MovementStateInfo = MovementStateInfoMap.Find(NewMovmenetState);
		if (MovementStateInfo)
		{
			bOrientRotationToMovement = MovementStateInfo->bOrientRotationToMovement;
			RotationRate = MovementStateInfo->RotationRate;
			JumpZVelocity = MovementStateInfo->JumpZVelocity;
		}
		break;
	}
	case EDesertFoxMovementState::Jumping:
		bOrientRotationToMovement = false;
		break;
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
	// Jumping 상태는 Save 하지 않음
	if (OldMovmenetState == EDesertFoxMovementState::Jumping || OldMovmenetState == EDesertFoxMovementState::None)
		return;

	LastMovementState = OldMovmenetState;
	LastMaxSpeed = GetMaxSpeed();
}

void UDesertFoxMovementComponent::RestoreMovmenetState(bool bForceUpdate)
{
	if (!bForceUpdate)
	{
		// Jumping 상태에서는 Restore 하지 않음
		if (CurrentMovementState == EDesertFoxMovementState::Jumping)
			return;
	}

	if (IsValid(CharacterOwner))
	{
		APlayerController* PlayerController = CharacterOwner->GetController<APlayerController>();
		if (IsValid(PlayerController))
		{
			// 특수 상태로 Restore 할 때, 해당 키를 누르고 있지 않다면 Idle 상태로 되돌림
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