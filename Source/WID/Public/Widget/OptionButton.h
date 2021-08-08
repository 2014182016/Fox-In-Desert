// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WIDUserWidget.h"
#include "OptionButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIndexChanged, int32, CurrentIndex);

/**
 * 
 */
UCLASS()
class WID_API UOptionButton : public UWIDUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE int32 GetCurrentIndex() const { return CurrentIndex; }

	/** Set the current text according to the index */
	UFUNCTION(BlueprintCallable)
		virtual void SetIndex(const int32 NewIndex);

protected:
	// {{ UUserWidget Interface
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	// }} UUserWidget Interface

protected:
	/** Called when left button is clicked */
	UFUNCTION()
		void OnClickLeftButton();
	/** Called when right button is clicked */
	UFUNCTION()
		void OnClickRightButton();

public:
	/** Called when left button or right button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnIndexChanged OnIndexChanged;

protected:
	/** Press this button to decrease the current index */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* LeftButton;

	/**Press this button to increase the current index */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UButton* RightButton;

	/** Text to display in UI based on current index */
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
		class UTextBlock* DisplayText;

	/** List of names to display in UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content", meta = (AllowPrivateAccess = true))
		TArray<FName> NameList;

	/** Index to display at startup */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content", meta = (AllowPrivateAccess = true))
		int32 DefaultIndex;

protected:
	int32 CurrentIndex;

};
