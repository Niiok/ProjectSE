// Fill out your copyright notice in the Description page of Project Settings.


#include "SEGameState.h"
#include "Net/UnrealNetwork.h"




void ASEGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASEGameState, OpenedFloors);
}

bool ASEGameState::IsFloorOpened(uint8 InFloor) const
{
	return OpenedFloors & (1ll << InFloor);
}

void ASEGameState::OnRep_OpenedFloors(uint64 OpenedFloors_Old)
{
	uint64 Diff = OpenedFloors ^ OpenedFloors_Old;

	for (int32 i = 0; i < sizeof(OpenedFloors) * 8; ++i)
	{
		uint64 Mask = 1ll << i;

		if (Diff & Mask)
		{
			OnFloorStateChanged.Broadcast(i, OpenedFloors & Mask);
		}
	}
}
