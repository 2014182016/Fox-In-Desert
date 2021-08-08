// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OptionButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UOptionButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetIndex(DefaultIndex);
}

void UOptionButton::NativeConstruct()
{
	Super::NativeConstruct();

	SetIndex(DefaultIndex);

	LeftButton->OnClicked.AddDynamic(this, &UOptionButton::OnClickLeftButton);
	RightButton->OnClicked.AddDynamic(this, &UOptionButton::OnClickRightButton);
}

void UOptionButton::OnClickLeftButton()
{
	SetIndex(CurrentIndex - 1);
}

void UOptionButton::OnClickRightButton()
{
	SetIndex(CurrentIndex + 1);
}

void UOptionButton::SetIndex(const int32 NewIndex)
{
	if (NameList.IsValidIndex(NewIndex))
	{
		CurrentIndex = NewIndex;
		if (OnIndexChanged.IsBound())
		{
			OnIndexChanged.Broadcast(CurrentIndex);
		}

		DisplayText->SetText(FText::FromName(NameList[CurrentIndex]));
	}
}