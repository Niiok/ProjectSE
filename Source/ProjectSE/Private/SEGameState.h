// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SEGameState.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFloorStateChanged, uint8, bool);

/**
 * 
 */
UCLASS()
class ASEGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	friend class ASEGameMode;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	UFUNCTION(BlueprintPure)
	bool IsFloorOpened(uint8 InFloor) const;

	void RegisterElevator(class AElevator* InElevator);
	bool IsElevatorReady() const;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void Multicast_OpenElevator();

protected:
	UFUNCTION()
	void OnRep_OpenedFloors(uint64 OpenedFloors_Old);


public:
	FOnFloorStateChanged OnFloorStateChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_OpenedFloors)
	uint64 OpenedFloors;

	TWeakObjectPtr<class AElevator> ElevatorActor;
};
