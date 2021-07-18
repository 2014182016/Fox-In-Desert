// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStateWidget.h"
#include "Core/WIDPlayerState.h"
#include "Components/Image.h"

void UPlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateStaminaGauge();
}

void UPlayerStateWidget::UpdateHudEvent(const EHudEvent HudEvent, const WID::THudEventInfoList& HudEventInfoList)
{
	Super::UpdateHudEvent(HudEvent, HudEventInfoList);

	switch (HudEvent)
	{
	case EHudEvent::Update:
		if (!bUpdateStamina)
		{
			bUpdateStamina = true;
			PlayAnimation(StaminaAppearAnim);
		}
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
		const float CurrentStamina = WIdPlayerState->GetCurrentStamina();
		const float MaxStamina = WIdPlayerState->GetMaxStamina();
		const float StaminaProgress = (MaxStamina < FLT_EPSILON) ? 0.0f : FMath::Clamp<float>(CurrentStamina / MaxStamina, 0.0f, 1.0f);

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