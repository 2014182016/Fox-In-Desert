// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WIDAnimInstance.generated.h"

/** Enumeration showing lazy state */
UENUM()
enum class ELazyState : uint8
{
	None,
	Idle,
	Lie,
	Sleep,
	WakeUp,
};

/** Status information required for lazy state */
USTRUCT(BlueprintType)
struct FLazyStateInfo
{
	GENERATED_USTRUCT_BODY()

public:
	/** Returns the list of animation indexes required for the state condition */
	static TArray<int32> GetAnimIndexList(const TArray<FLazyStateInfo>& InfoList, const ELazyState CurrentState);
	/** Returns the list of probabilitiy required for the state condition */
	static TArray<int32> GetProbList(const TArray<FLazyStateInfo>& InfoList, const ELazyState CurrentState);

public:
	/** Specified lazy state */
	UPROPERTY(EditDefaultsOnly)
		ELazyState LazyState;
	/** Desired animation index */
	UPROPERTY(EditDefaultsOnly)
		int32 AnimIndex;
	/** Probability for selecting the animation index */
	UPROPERTY(EditDefaultsOnly)
		int32 Probability;
};

/**
 * 
 */
UCLASS()
class WID_API UWIDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// {{ UAnimInstance Interface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// }} UAnimInstance Interface

public:
	/** Random death animation play */
	void PlayDeathAnimation();

	/** Randomize the index of the next lazy animation */
	UFUNCTION(BlueprintCallable)
		void SettingLazyAnimRandomIndex();

protected:
	/** Perform the function every tick when in the lazy state */
	virtual void TickLazyState(float DeltaSeconds);

	/** Call at start of lazy state */
	virtual void BeginLazyState();

	/** Reset the required information from the lazy state */
	UFUNCTION(BlueprintCallable)
		virtual void ResetLazyState();

	/** Call at end of lazy state */
	UFUNCTION(BlueprintCallable)
		virtual void EndLazyState();

	/** Return the time required for the next animation */
	float GetNextLazyAnimTime() const;

	/** Specifies the current lazy state */
	void SetLazyState(ELazyState NewState);

protected:
	/** Curve for jump animation rate to determin distance from ground */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		class UCurveFloat* JumpAnimRateCurve;

	/** Jump animation start point for natural animation. If the character can ready to jump, set to default value */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float JumpAnimStartPosition = 0.0f;

	/** Time to reach lazy state */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float LazyStateTime = 15.0f;

	/** Time to reach lie State */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float LieStateTime = 60.0f;

	/** Time to reach sleep State */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float SleepStateTime = 30.0f;

	/** List of state information required by lazy state */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		TArray<FLazyStateInfo> LazyInfoList;

	/** Randomly specify the time to play the next animation, X is minimum value, Y is maximum value */
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		FVector2D LazyAnimRandomTime = FVector2D(5.0f, 10.0f);

protected:
	/** Is the character floating in the air? */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		uint32 bIsInAir : 1;

	/** Is the character walking slowly? */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		uint32 bIsSlowWalking : 1;

	/** Is the character jumping? */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		uint32 bIsJumping : 1;

	/** The current speed at which the character moves */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CurrentSpeed;

	/** The current speed at which the character moves based on the X and Y axes */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CurrentSpeed2D;

	/** how far the character looks to the direction */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CurrentLookDegree;

	/** Rate of jump animation. The character's jump animation rate varies depneing on the distance from ground */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float JumpAnimRate = 1.0f;

	/** How fast you'll play the animation you're looking at */
	UPROPERTY(Transient, EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float LookAnimRate = 1.0f;

	/** On death, another state machine will be activated */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		uint32 bDied : 1;

	/** Index of death animation to play is specified randomly when died */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		int32 DeathAnimationIndex;

	/** Show which state the character is in */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		ELazyState CurrentLazyState;

	/** Lazy animation index to play */
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = true))
		int32 LazyAnimIndex;

private:
	/** Remaining Time to specify next lazy animation */
	float NextLazyAnimTime;

	/** Time character have maintained lazy state so far */
	float LazyStateStamp;

	/** Is the character in the lazy state? */
	bool bIsInLazyState;
};
