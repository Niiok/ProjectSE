// Fill out your copyright notice in the Description page of Project Settings.


#include "SESaveGame.h"




bool USESaveGame::IsFloorOpened(uint8 InFloor) const
{
	return OpenedFloors & (1ll << InFloor);
}

bool USESaveGame::SetFloorOpened(uint8 InFloor)
{
	if (InFloor < sizeof(OpenedFloors) * 8 && IsFloorOpened(InFloor) == false)
	{
		OpenedFloors |= (1ll << InFloor);
		return true;
	}

	return false;
}

bool USESaveGame::SetFloorClosed(uint8 InFloor)
{
	if (InFloor < sizeof(OpenedFloors) * 8 && IsFloorOpened(InFloor))
	{
		OpenedFloors &= ~(1 << InFloor);
		return true;
	}

	return false;
}
