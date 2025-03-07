// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASEPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;


public:
	class UInteractionComponent* GetFocusingInteraction() const { return FocusingInteraction.Get(); }


protected:
	TWeakObjectPtr<class UInteractionComponent> FocusingInteraction;
};
