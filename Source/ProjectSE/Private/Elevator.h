// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS()
class AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	AElevator();

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseDoor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	bool IsClosed() const;
};
