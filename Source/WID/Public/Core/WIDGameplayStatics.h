// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "WIDGameplayStatics.generated.h"



/**
 * 
 */
UCLASS()
class WID_API UWIDGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

public:
	static int32 GetRandomIndexByProbability(const TArray<int32>& Probabilities);

};
