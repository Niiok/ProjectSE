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
	virtual void OnComponentCreated() override;

	virtual bool IsInteractable(class ASECharacter* InInteractor) const override { return bIsDropped == false && bIsFloorOpened; }
	virtual bool IsHoldable(class ASECharacter* InHolder) const override { return bIsDropped; }
	virtual bool IsUnholdable(class ASECharacter* InUnHolder) const override { return bIsDropped; }
	virtual void Interact(class ASECharacter* InInteractor) override;

protected:
	virtual void BeginPlay() override;


public:
	uint8 GetFloorNumber() const { return FloorNumber; }

protected:
	void OnFloorStateChanged(uint8 InFloor, bool bIsOpened);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* NumberComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTransform NumberTransform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 NumberSize = 16;

	UPROPERTY(EditAnywhere)
	uint8 FloorNumber = UINT8_MAX;

	bool bIsDropped = false;
	bool bIsFloorOpened = false;
};
