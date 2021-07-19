// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WIDTypes.h"
#include "GameFramework/PlayerController.h"
#include "WIDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WID_API AWIDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	DECLARE_DELEGATE_OneParam(FCameraMode, int32);

public:
	// {{ APlayerController interface
	virtual void SetupInputComponent() override;
	// }} APlayerController interface

	// {{ Bind Axis Function
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void Turn(const float Value);
	void LookUp(const float Value);
	// }} Bind Axis Function

	// {{ Bind Action Function
	void StartJump();
	void StopJump();
	void StartRun();
	void StopRun();
	void StartSlowWalk();
	void StopSlowWalk();
	void StartLookLeft();
	void StopLookLeft();
	void StartLookRight();
	void StopLookRight();
	UFUNCTION(exec) void ChangeCameraMode(const int32 NewMode);
	UFUNCTION(exec) void ToggleMainMenu();
	// }} Bind Action Function

protected:
	/** The speed at which the screen is rotated depends on the this variable */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float MouseSensitivity = 45.0f;

	/* If true, Pawn looks in the direction the controller sees. If not, Pawn rotates according to the inputs */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		bool bUsePawnControlRotation = true;
};
