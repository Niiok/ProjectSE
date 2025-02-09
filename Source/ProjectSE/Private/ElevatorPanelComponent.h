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
	virtual void Auth_Interact(class ASECharacter* InInteractor) override;

};
