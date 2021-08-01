// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "WIDPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class WID_API AWIDPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	/** Because the camera fades only the currently rendered screen, it allows the UI to fade as well */
	UFUNCTION(BlueprintCallable, Category = "Camera Fades")
		virtual void StartCameraFadeWithUI(float FromAlpha, float ToAlpha, float Duration, FLinearColor Color, bool bShouldFadeAudio = false, bool bHoldWhenFinished = false);

	class AWIDHUD* GetOwningHUD();

protected:
	// {{ APlayerCameraManager Interface
	virtual void DoUpdateCamera(float DeltaTime) override;
	virtual void StopCameraFade() override;
	// }} APlayerCameraManager Interface

protected:
	/** Update Opacity to fade UI */
	void UpdateUIFade(const float Amount);

protected:
	UPROPERTY(Transient)
		class AWIDHUD* WIDHUD;

private:
	/** Enable Update the UI fade */
	bool bEnableUIFading;

};
