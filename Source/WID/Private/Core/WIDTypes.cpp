// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDTypes.h"

bool WID::CheckEventInfo(THudEventInfo EvnetInfo)
{
	return EvnetInfo.IsEmpty();
}

bool WID::CheckEventInfo(THudEventInfoList EvnetInfoList, int32 Index)
{
	if (EvnetInfoList.IsValidIndex(Index))
	{
		return EvnetInfoList[Index].IsEmpty();
	}
	return false;
}