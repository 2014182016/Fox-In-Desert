// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WIDAnimInstance.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDMovementComponent.h"
#include "Core/WIDGameplayStatics.h"
#include "Curves/CurveFloat.h"

TArray<int32> FLazyStateInfo::GetAnimIndexList(const TArray<FLazyStateInfo>& InfoList, const ELazyState CurrentState)
{
	TArray<int32> Result;

	for (const FLazyStateInfo& Info : InfoList)
	{
		if (Info.LazyState == CurrentState)
		{
			Result.Emplace(Info.AnimIndex);
		}
	}

	return Result;
}

TArray<int32> FLazyStateInfo::GetProbList(const TArray<FLazyStateInfo>& InfoList, const ELazyState CurrentState)
{
	TArray<int32> Result;

	for (const FLazyStateInfo& Info : InfoList)
	{
		if (Info.LazyState == CurrentState)
		{
			Result.Emplace(Info.Probability);
		}
	}

	return Result;
}

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
		bIsInLazyState = (GetWorld()->GetTimeSeconds() - WIDCharacter->LastMoveStamp > LazyStateTime) ? true : false;
		if (bIsInLazyState || CurrentLazyState != ELazyState::None)
		{
			TickLazyState(DeltaSeconds);
			return;
		}
		LazyStateStamp = 0.0f;

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

void UWIDAnimInstance::TickLazyState(float DeltaSeconds)
{
	if (LazyStateStamp <= 0.0f)
	{
		BeginLazyState();
	}

	switch (CurrentLazyState)
	{
	case ELazyState::Idle:
		if (!bIsInLazyState)
		{
			SetLazyState(ELazyState::None);
		}
		else if (LazyStateStamp >= LazyStateTime + LieStateTime)
		{
			SetLazyState(ELazyState::Lie);
		}
		break;
	case ELazyState::Lie:
		if (!bIsInLazyState)
		{
			SetLazyState(ELazyState::WakeUp);
		}
		else if (LazyStateStamp >= LazyStateTime + LieStateTime + SleepStateTime)
		{
			SetLazyState(ELazyState::Sleep);
		}
		break;
	case ELazyState::Sleep:
		if (!bIsInLazyState)
		{
			SetLazyState(ELazyState::WakeUp);
		}
		return;
	case ELazyState::WakeUp:
		return;
	}

	if (NextLazyAnimTime <= 0.0f)
	{
		NextLazyAnimTime = GetNextLazyAnimTime();
		SettingLazyAnimRandomIndex();
	}

	NextLazyAnimTime -= DeltaSeconds;
	LazyStateStamp += DeltaSeconds;
}

void UWIDAnimInstance::BeginLazyState()
{
	SettingLazyAnimRandomIndex();
	SetLazyState(ELazyState::Idle);
}

void UWIDAnimInstance::EndLazyState()
{
	SetLazyState(ELazyState::None);
}

void UWIDAnimInstance::ResetLazyState()
{
	NextLazyAnimTime = GetNextLazyAnimTime();
	LazyAnimIndex = 0;
}

float UWIDAnimInstance::GetNextLazyAnimTime() const
{
	return FMath::FRandRange(LazyAnimRandomTime.X, LazyAnimRandomTime.Y);
}

void UWIDAnimInstance::SettingLazyAnimRandomIndex()
{
	TArray<int32> IndexList = FLazyStateInfo::GetAnimIndexList(LazyInfoList, CurrentLazyState);
	TArray<int32> ProbList = FLazyStateInfo::GetProbList(LazyInfoList, CurrentLazyState);
	
	// Remove previously used index, but leaves 0 as is
	if (ProbList.IsValidIndex(LazyAnimIndex) && LazyAnimIndex != 0)
	{
		ProbList.RemoveSwap(LazyAnimIndex);
		
		// If the index is removed, it is removed from IndexList
		if (IndexList.IsValidIndex(LazyAnimIndex))
		{
			IndexList.RemoveAt(LazyAnimIndex);
		}
	}

	LazyAnimIndex = UWIDGameplayStatics::GetRandomIndexByProbability(ProbList);
	if (IndexList.IsValidIndex(LazyAnimIndex))
	{
		// Convert index from IndexList
		LazyAnimIndex = IndexList[LazyAnimIndex];
	}
}

void UWIDAnimInstance::SetLazyState(ELazyState NewState)
{
	CurrentLazyState = NewState;

	switch (CurrentLazyState)
	{
	case ELazyState::None:
	{
		// Release the sleep state and allow it to move
		AWIDCharacter* WIDCharacter = Cast<AWIDCharacter>(TryGetPawnOwner());
		if (IsValid(WIDCharacter))
		{
			WIDCharacter->WakeUp();
		}
		break;
	}
	case ELazyState::Lie:
	{
		// Judging that character hasn't moved for a long time, character goes into sleep
		AWIDCharacter* WIDCharacter = Cast<AWIDCharacter>(TryGetPawnOwner());
		if (IsValid(WIDCharacter))
		{
			WIDCharacter->Sleep();
		}
		break;
	}
	}
}
