// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStateWidget.h"
#include "Core/WIDPlayerState.h"
#include "Components/Image.h"

void UPlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateStaminaGauge();
}

void UPlayerStateWidget::UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList)
{
	Super::UpdateHudEvent(HudEvent, HudEventInfoList);

	switch (HudEvent)
	{
	case EHudEvent::UpdateStamina:
		if (!bUpdateStamina)
		{
			bUpdateStamina = true;
			PlayAnimation(StaminaAppearAnim);
		}
		break;
	case EHudEvent::UpdateHealth:
		UpdateHealthGauge();
		break;
	}
}

void UPlayerStateWidget::UpdateStaminaGauge()
{
	if (!bUpdateStamina || !StaminaGauge)
		return;

	AWIDPlayerState* WIdPlayerState = GetOwningPlayerState<AWIDPlayerState>();
	if (IsValid(WIdPlayerState))
	{
		const float StaminaProgress = WIdPlayerState->GetStaminaPercent();

		UMaterialInstanceDynamic* GaugeMaterialInstance = StaminaGauge->GetDynamicMaterial();
		if (GaugeMaterialInstance)
		{
			GaugeMaterialInstance->SetScalarParameterValue(FName("Progress"), StaminaProgress);
		}

		if (StaminaProgress >= 1.0f)
		{
			bUpdateStamina = false;
			PlayAnimationReverse(StaminaAppearAnim);
		}
	}
}

void UPlayerStateWidget::UpdateHealthGauge()
{
	AWIDPlayerState* WIdPlayerState = GetOwningPlayerState<AWIDPlayerState>();
	if (IsValid(WIdPlayerState))
	{
		const float HealthProgress = WIdPlayerState->GetHealthPercent();

		UMaterialInstanceDynamic* GaugeMaterialInstance = HealthGauge->GetDynamicMaterial();
		if (GaugeMaterialInstance)
		{
			GaugeMaterialInstance->SetScalarParameterValue(FName("Progress"), HealthProgress);
		}
	}
}