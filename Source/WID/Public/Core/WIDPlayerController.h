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
	DECLARE_DELEGATE_OneParam(FSensitivityType, float);

public:
	// {{ AController interface
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	// }} AController interface

	// {{ APlayerController interface
	virtual void SetupInputComponent() override;
	// }} APlayerController interface

public:
	/** Call by player state when character died */
	virtual void NotifyDied();

	/** Use enum to simply set up input mode */
	UFUNCTION(BlueprintCallable)
		virtual void SetSimpleInputMode(const EInputMode NewInputMode);

	// {{ Bind Action Function
	UFUNCTION(exec)
		void ToggleGameMenu();
	// }} Bind Action Function

protected:
	// {{ AActor Interface
	virtual void BeginPlay() override;
	// }} AActor Interface

protected:
	// {{ Bind Axis Function
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void Turn(const float Value);
	void LookUp(const float Value);
	void CameraZoom(const float Value);
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
	UFUNCTION(exec)
		void ChangeCameraMode(const int32 NewMode);
	// }} Bind Action Function

	void StartCameraFade();

protected:
	/** If true, Pawn looks in the direction the controller sees. If not, Pawn rotates according to the inputs */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		bool bUsePawnControlRotation = true;

	/** You can adjust the distance from character through the mouse wheel.X is minimum length, Y is maximum length */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		FVector2D ZoomDistance = FVector2D(100.0f, 500.0f);

	/** The speed at which the distance is adjusted when the camera is adjusted throught the mouse wheel */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float ZoomSpeed = 50.0f;

	/** Input mode to specify when spawn controller */
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
		EInputMode StartInputMode;

	/** Input mode to specify when spawn controller */
	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float StartBlackScreenTime;

	/** Input mode to specify when spawn controller */
	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float StartFadeScreenTime;

};
