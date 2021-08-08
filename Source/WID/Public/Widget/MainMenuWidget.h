// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WIDUserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class WID_API UMainMenuWidget : public UWIDUserWidget
{
	GENERATED_BODY()

public:
	// {{ UWIDUserWidget Interface
	virtual void UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList) override;
	// }} UWIDUserWidget Interface

protected:
	// {{ UUserWidget Interface
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	// }} UUserWidget Interface

protected:
	/** Called when new game button is clicked */
	UFUNCTION()
		void OnClickNewGameButton();
	/** Called when continue game button is clicked */
	UFUNCTION()
		void OnClickContinueGameButton();
	/** Called when option button is clicked */
	UFUNCTION()
		void OnClickOptionButton();
	/** Called when exit button is clicked */
	UFUNCTION()
		void OnClickExitButton();
		
protected:
	/** Widget that allow you to change to other widgets */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UWidgetSwitcher* MenuWidgetSwitcher;

	/** Button to ignore existing saves and start a new game */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* NewGameButton;

	/** Button to call up existing saves and allow the game to continue */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ContinueGameButton;

	/** Button to change option widget */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* OptionButton;

	/** Button to exit the game */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* ExitButton;
};
