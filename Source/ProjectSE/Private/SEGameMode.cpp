// Fill out your copyright notice in the Description page of Project Settings.


#include "SEGameMode.h"

#include "Engine/SoftWorldReference.h"
#include "Kismet/GameplayStatics.h"
#include "Streaming/LevelStreamingDelegates.h"
#include "Elevator.h"




void ASEGameMode::BeginPlay()
{
	Super::BeginPlay();

	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &ASEGameMode::OnLevelAdded);
	FWorldDelegates::LevelRemovedFromWorld.AddUObject(this, &ASEGameMode::OnLevelRemoved);

	InitializeCurrentFloor();
}

void ASEGameMode::BeginDestroy()
{
	Super::BeginDestroy();

	FWorldDelegates::LevelAddedToWorld.RemoveAll(this);
	FWorldDelegates::LevelRemovedFromWorld.RemoveAll(this);
}

bool ASEGameMode::IsChangingFloor() const
{
	return UnloadingFloor.IsNull() == false || LoadingFloor.IsNull() == false;
}

void ASEGameMode::ChangeFloor(const struct FSoftWorldReference& InWorld)
{
	if (IsChangingFloor() || ElevatorActor.IsValid() == false || ElevatorActor->IsClosed() == false)
	{
		return;
	}

	LoadingFloor = InWorld.WorldAsset.ToSoftObjectPath();
	UnloadingFloor = CurrentFloor;

	if (IsChangingFloor())
	{
		UGameplayStatics::UnloadStreamLevel(this, UnloadingFloor.GetLongPackageFName(), FLatentActionInfo(), false);
	}
}

void ASEGameMode::RegisterElevator(class AElevator* InElevator)
{
	ElevatorActor = InElevator;
}

void ASEGameMode::InitializeCurrentFloor()
{
	for (const ULevelStreaming* StreamingLevel : GetWorld()->GetStreamingLevels())
	{
		if (StreamingLevel->ShouldBeAlwaysLoaded())
		{
			CurrentFloor = StreamingLevel->GetWorldAsset().ToSoftObjectPath();
			break;
		}
	}
}


void ASEGameMode::OnLevelRemoved(class ULevel* InLevel, class UWorld* InWorld)
{
	if (InWorld == GetWorld() && UnloadingFloor.GetAssetFName() == InLevel->GetOuter()->GetFName())
	{
		if (ensure(CurrentFloor == UnloadingFloor))
		{
			CurrentFloor.Reset();
		}

		UnloadingFloor.Reset();

		if (ensure(IsChangingFloor()))
		{
			UGameplayStatics::LoadStreamLevel(this, LoadingFloor.GetLongPackageFName(), true, false, FLatentActionInfo());
		}
		else
		{
			OnFloorChanged();
		}
	}
}

void ASEGameMode::OnLevelAdded(class ULevel* InLevel, class UWorld* InWorld)
{
	if (InWorld == GetWorld() && LoadingFloor.GetAssetFName() == InLevel->GetOuter()->GetFName())
	{
		CurrentFloor = LoadingFloor;
		LoadingFloor.Reset();

		if (ensure(IsChangingFloor() == false))
		{
			OnFloorChanged();
		}
	}
}

void ASEGameMode::OnFloorChanged()
{
	if (ElevatorActor.IsValid())
	{
		ElevatorActor->OpenDoor();
	}
}
