// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDGameplayStatics.h"

int32 UWIDGameplayStatics::GetRandomIndexByProbability(const TArray<int32>& Probabilities)
{
	int32 TotalSum = 0;
	for (const float Prob : Probabilities)
	{
		TotalSum += Prob;
	}

	int32 RandomNum = FMath::RandRange(0, TotalSum);
	TotalSum = 0;

	int32 ResultIndex = 0;
	for (; ResultIndex < Probabilities.Num(); ++ResultIndex)
	{
		TotalSum += Probabilities[ResultIndex];
		if (RandomNum < TotalSum)
		{
			break;
		}
	}

	return FMath::Clamp<int32>(ResultIndex, 0, Probabilities.Num());
}