// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SESaveGame.generated.h"

/**
 * 
 */
UCLASS()
class USESaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	bool IsFloorOpened(uint8 InFloor) const;
	uint64 GetOpenedFloors() const { return OpenedFloors; }

	bool SetFloorState(uint8 InFloor, bool bIsOpend);

protected:
	//UPROPERTY(VisibleAnywhere)
	//FString SaveSlotName;
	//UPROPERTY(VisibleAnywhere)
	//uint32 UserIndex;

	UPROPERTY()
	uint64 OpenedFloors;
};
