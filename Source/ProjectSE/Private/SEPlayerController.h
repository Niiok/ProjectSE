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
	
	ASEPlayerController();

public:
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TryInteract();


protected:
	TWeakObjectPtr<class UInteractionComponent> CurrentInteraction;
};
