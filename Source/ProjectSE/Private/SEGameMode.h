// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SEGameMode.generated.h"

/**
 *
 */
UCLASS()
class ASEGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;


public:
	UFUNCTION(BlueprintPure)
	bool IsChangingFloor() const;

	UFUNCTION(BlueprintCallable)
	void ChangeFloor(const struct FSoftWorldReference& InWorld);

	void RegisterElevator(class AElevator* InElevator);

protected:
	void InitializeCurrentFloor();
	void OnLevelRemoved(class ULevel* InLevel, class UWorld* InWorld);
	void OnLevelAdded(class ULevel* InLevel, class UWorld* InWorld);
	void OnFloorChanged();

protected:
	FSoftObjectPath CurrentFloor;
	FSoftObjectPath UnloadingFloor;
	FSoftObjectPath LoadingFloor;
	TWeakObjectPtr<class AElevator> ElevatorActor;
};