// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DesertFoxTypes.h"
#include "OptionalWrapper.h"
#include "GameFramework/Character.h"
#include "DesertFoxCharacter.generated.h"

UCLASS()
class ADesertFoxCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADesertFoxCharacter(const FObjectInitializer& ObjectInitializer);

	// {{ ACharacter Interface
	virtual void Landed(const FHitResult& Hit) override;
	// }} ACharacter Interface

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	void Run();
	void SlowWalk();

	void SaveMovementState();
	void RestoreMovementState();

	void StartJump();
	void RealJump();
	bool CanReadyToJump() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

private:
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		FOptionalFloat ReadyToJumpTime = 0.2f;

};

