// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainMenuWidget.h"
#include "Core/WIDGameInstance.h"
#include "Core/WIDSaveGame.h"
#include "../WID.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Active main menu widget
	MenuWidgetSwitcher->SetActiveWidgetIndex(0);

	NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickNewGameButton);
	ContinueGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickContinueGameButton);
	OptionButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickOptionButton);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickExitButton);
}

FReply UMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().IsValid() && InKeyEvent.GetKey() == EKeys::Escape)
	{
		// OptionWidget Activated
		if (MenuWidgetSwitcher->GetActiveWidgetIndex() == 1)
		{
			MenuWidgetSwitcher->SetActiveWidgetIndex(0);
		}
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMainMenuWidget::UpdateHudEvent(const EHudEvent HudEvent, const WID::FHudEventInfoList& HudEventInfoList)
{
	Super::UpdateHudEvent(HudEvent, HudEventInfoList);

	switch (HudEvent)
	{
	case EHudEvent::WidgetSwitcher:
		if (WID::CheckEventInfo(HudEventInfoList, 0))
		{
			const int32 ActiveIndex = HudEventInfoList[0].GetValue<int32>();
			MenuWidgetSwitcher->SetActiveWidgetIndex(ActiveIndex);
		}
		break;
	}
}

void UMainMenuWidget::OnClickNewGameButton() EmptyFunction

void UMainMenuWidget::OnClickContinueGameButton()
{
	UWIDGameInstance* WIDGameInstance = Cast<UWIDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (WIDGameInstance)
	{
		UWIDSaveGame* WIDSaveGame = WIDGameInstance->LoadGame();
		if (WIDSaveGame)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/WID/Maps/LoadingMap")), true, TEXT("NextLevel=/Game/StylizedDesertEnv/Maps/Demonstration"));
		}
		else
		{
			WID_LOG(Display, TEXT("Does not exist saved data"));
		}
	}
	else
	{
		WID_LOG(Display, TEXT("Does not exist saved data"));
	}
}

void UMainMenuWidget::OnClickOptionButton()
{
	// Active option widget
	MenuWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UMainMenuWidget::OnClickExitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}