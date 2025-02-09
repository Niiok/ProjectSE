// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SoftWorldReference.h"
#include "GameFramework/GameModeBase.h"

#include "SEGameMode.generated.h"


/**
 *
 */
UCLASS()
class ASEGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ASEGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
public:
	virtual void InitGameState() override;


public:
	void SetFloorState(uint8 InFloor, bool bIsOpened);

	UFUNCTION(BlueprintPure)
	bool IsChangingFloor() const;

	UFUNCTION(BlueprintCallable)
	void ChangeFloor(const struct FSoftWorldReference& InWorld);
	void ChangeFloor(uint8 InFloor);

protected:
	class USESaveGame* GetSaveGame() const;
	void Save();

	void InitializeCurrentFloor();
	void OnLevelRemoved(class ULevel* InLevel, class UWorld* InWorld);
	void OnLevelAdded(class ULevel* InLevel, class UWorld* InWorld);
	void OnFloorChanged();


protected:
	UPROPERTY(EditAnywhere)
	TMap<uint8, struct FSoftWorldReference> FloorToLevel;
	UPROPERTY(EditAnywhere)
	uint8 StartingFloor;

	UPROPERTY(Transient)
	mutable class USESaveGame* SaveGame;

	FSoftObjectPath CurrentFloor;
	FSoftObjectPath UnloadingFloor;
	FSoftObjectPath LoadingFloor;
};