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
	/** Characater turns into a running movement state */
	void Run();
	/** Characater turns into a slow walking movement state */
	void SlowWalk();
	/** Characater turns into a previous movement state  */
	void RestoreMovementState();

	/** Characater begins to prepare for the jump  */
	void StartJump();
	/** Characater performs jump */
	void RealJump();
	/** Returns true if the character can ready to jump */
	bool CanReadyToJump() const;

protected:
	/** Binding the camera to the character for fixed distance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Third person camera for player*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

private:
	/* If the value is set, the jump is executed after a certain period of time. If not, it's done immediately */
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		FOptionalFloat ReadyToJumpTime = 0.2f;

};

