// Fill out your copyright notice in the Description page of Project Settings.


#include "SESaveGame.h"




bool USESaveGame::IsFloorOpened(uint8 InFloor) const
{
	return OpenedFloors & (1ll << InFloor);
}

bool USESaveGame::SetFloorState(uint8 InFloor, bool bIsOpend)
{
	if (InFloor < sizeof(OpenedFloors) * 8 && IsFloorOpened(InFloor) != bIsOpend)
	{
		if (bIsOpend)
		{
			OpenedFloors |= (1ll << InFloor);
		}
		else
		{
			OpenedFloors &= ~(1ll << InFloor);
		}
		return true;
	}

	return false;
}


int64 USESaveGame::GetInteractionState(const FSoftObjectPath& InPath) const
{
	if (auto Findee = InteractionStates.Find(InPath))
	{
		return *Findee;
	}

	return 0;
}

void USESaveGame::SetInteractionState(const FSoftObjectPath& InPath, int64 InState)
{
	InteractionStates.FindOrAdd(InPath) = InState;
}
