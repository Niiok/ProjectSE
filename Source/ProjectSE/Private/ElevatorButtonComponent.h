// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "ElevatorButtonComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class UElevatorButtonComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:
	virtual bool IsInteractable(class ASECharacter* InInteractor) const override { return bIsDropped == false && bIsFloorOpened; }
	virtual bool IsHoldable(class ASECharacter* InHolder) const override { return bIsDropped; }
	virtual bool IsUnHoldable(class ASECharacter* InUnHolder) const override { return bIsDropped; }
	virtual int64 Auth_Interact(class ASECharacter* InInteractor, int64 InParam) override;

protected:
	virtual void BeginPlay() override;


public:
	uint8 GetFloorNumber() const { return FloorNumber; }

protected:
	void OnFloorStateChanged(uint8 InFloor, bool bIsOpened);
	void AdjustText();


protected:
	UPROPERTY(EditAnywhere)
	uint8 FloorNumber = UINT8_MAX;

	bool bIsDropped = false;
	bool bIsFloorOpened = false;
};
