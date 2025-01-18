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
	UFUNCTION(BlueprintPure)
	bool IsFloorOpened(uint8 InFloor) const;

	UFUNCTION(BlueprintCallable)
	bool SetFloorOpened(uint8 InFloor);
	UFUNCTION(BlueprintCallable)
	bool SetFloorClosed(uint8 InFloor);

protected:
	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere)
	uint32 UserIndex;

	UPROPERTY()
	uint64 OpenedFloors;
};
