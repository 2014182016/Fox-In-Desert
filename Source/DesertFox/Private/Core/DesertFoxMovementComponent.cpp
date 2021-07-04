// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DesertFoxMovementComponent.h"
#include "GameFramework/Character.h"

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
		FMovemenetStateInfo MovementStateInfo = MovementStateInfoMap[NewMovmenetState];
		bOrientRotationToMovement = MovementStateInfo.bOrientRotationToMovement;
		RotationRate = MovementStateInfo.RotationRate;
		JumpZVelocity = MovementStateInfo.JumpZVelocity;
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
	// Jumping ���´� Save ���� ����
	if (OldMovmenetState == EDesertFoxMovementState::Jumping)
		return;

	LastMovementState = OldMovmenetState;
	LastMaxSpeed = GetMaxSpeed();
}

void UDesertFoxMovementComponent::RestoreMovmenetState()
{
	// Jumping ���´� Restore ���� ����
	if (LastMovementState == EDesertFoxMovementState::Jumping)
		return;

	if (IsValid(CharacterOwner))
	{
		APlayerController* PlayerController = CharacterOwner->GetController<APlayerController>();
		if (IsValid(PlayerController))
		{
			// Ư�� ���·� Restore �� ��, �ش� Ű�� ������ ���� �ʴٸ� Idle ���·� �ǵ���
			if ((LastMovementState == EDesertFoxMovementState::Running) && !PlayerController->IsInputKeyDown(EKeys::LeftShift))
				LastMovementState = EDesertFoxMovementState::Idle;
			if ((LastMovementState == EDesertFoxMovementState::SlowWalking) && !PlayerController->IsInputKeyDown(EKeys::LeftControl))
				LastMovementState = EDesertFoxMovementState::Idle;
		}
	}

	SetMovementState(LastMovementState);
}
