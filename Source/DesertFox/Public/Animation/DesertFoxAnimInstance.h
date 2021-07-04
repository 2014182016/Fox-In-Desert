// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DesertFoxAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DESERTFOX_API UDesertFoxAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bIsInAir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bIsSlowWalking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		bool bIsJumping;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
		float CurrentSpeed;
};
