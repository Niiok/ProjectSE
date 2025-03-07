// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "ElevatorPanelComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class UElevatorPanelComponent : public UInteractionComponent
{
	GENERATED_BODY()
	
public:
	virtual bool IsInteractable(class ASECharacter* InInteractor) const override;
	virtual int64 Auth_Interact(class ASECharacter* InInteractor, int64 InParam) override;

};
