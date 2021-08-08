// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionDetailWidget.h"
#include "GameplayOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UGameplayOptionWidget : public UOptionDetailWidget
{
	GENERATED_BODY()
	
protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	// }} UUserWidget Interface

protected:
	// {{ UOptionDetailWidget Interface
	virtual void UpdateGameSettings() override;
	// }} UOptionDetailWidget Interface

	/** Called when language option button is clicked */
	UFUNCTION()
		void OnIndexChangedLanguageOptionButton(const int32 Index);
	/** Called when tilt body checkbox state is changed */
	UFUNCTION()
		void OnCheckStateChangedTiltBodyCheckBox(const bool Value);

protected:
	/** Localization is applied to UI by changing language */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UOptionButton* LanguageOptionButton;

	/** Adjust the tilt body setting using this check box */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UCheckBox* TiltBodyCheckBox;

};
