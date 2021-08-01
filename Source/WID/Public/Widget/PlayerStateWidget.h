// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WIDUserWidget.h"
#include "PlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UPlayerStateWidget : public UWIDUserWidget
{
	GENERATED_BODY()

public:
	/** Receive events from the hud and do the desired actions in this widget */
	virtual void UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList) override;

protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// }} UUserWidget Interface

protected:
	/** If bUpdateStamina is true, update stamian gauge */
	void UpdateStaminaGauge();

	/** Update health gauge using player state */
	void UpdateHealthGauge();

	/** Update the state of stamina so that the player is aware of it */
	void UpdateStaminaState(const EStaminaState NewStaminaState);

protected:
	/** Display the playerstate's stamina as a value between 0 and 1 */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UImage* StaminaGauge;

	/** Display the playerstate's health as a value between 0 and 1 */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UImage* HealthGauge;

	/** Perform an animation that disappears when stamina is 0, and appears when it is 1 */
	UPROPERTY(Transient, meta = (AllowPrivateAccess = true, BindWidgetAnim))
		class UWidgetAnimation* StaminaAppearAnim;

	/** An animation indicating the state of stamina */
	UPROPERTY(Transient, meta = (AllowPrivateAccess = true, BindWidgetAnim))
		class UWidgetAnimation* ChangeStaminaStateAnim;

private:
	/** Whether to update stamina gauge or not */
	bool bUpdateStamina;
	
};
