// Fill out your copyright notice in the Description page of Project Settings.


#include "SEGameMode.h"

#include "Engine/SoftWorldReference.h"
#include "Kismet/GameplayStatics.h"
#include "SEGameState.h"
#include "SESaveGame.h"
#include "Streaming/LevelStreamingDelegates.h"





static const FString SaveSlot = TEXT("SaveSlot");
static constexpr int32 SaveIndex = 1;

ASEGameMode::ASEGameMode()
{
	GameStateClass = ASEGameState::StaticClass();
}

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

	Save();
}

void ASEGameMode::InitGameState()
{
	Super::InitGameState();

	if (ASEGameState* GS = GetGameState<ASEGameState>())
	{
		GS->OpenedFloors = GetSaveGame()->GetOpenedFloors();
	}
}

void ASEGameMode::SetFloorState(uint8 InFloor, bool bIsOpened)
{
	if (GetSaveGame()->SetFloorState(InFloor, bIsOpened))
	{
		if (ASEGameState* GS = GetGameState<ASEGameState>())
		{
			auto OldValue = GS->OpenedFloors;
			GS->OpenedFloors = GetSaveGame()->GetOpenedFloors();
			GS->OnRep_OpenedFloors(OldValue);
		}
	}
}

bool ASEGameMode::IsChangingFloor() const
{
	return UnloadingFloor.IsNull() == false || LoadingFloor.IsNull() == false;
}

void ASEGameMode::ChangeFloor(const struct FSoftWorldReference& InWorld)
{
	ASEGameState* GS = GetGameState<ASEGameState>();

	if (IsChangingFloor() || GS == nullptr || GS->IsElevatorReady() == false)
	{
		return;
	}

	LoadingFloor = InWorld.WorldAsset.ToSoftObjectPath();
	UnloadingFloor = CurrentFloor;

	if (LoadingFloor.GetAssetFName() == UnloadingFloor.GetAssetFName())
	{
		LoadingFloor.Reset();
		UnloadingFloor.Reset();
		OnFloorChanged();
		return;
	}

	if (UnloadingFloor.IsNull() == false)
	{
		UGameplayStatics::UnloadStreamLevel(this, UnloadingFloor.GetLongPackageFName(), FLatentActionInfo(), false);
	}
	else if (LoadingFloor.IsNull() == false)
	{
		UGameplayStatics::LoadStreamLevel(this, LoadingFloor.GetLongPackageFName(), true, false, FLatentActionInfo());
	}
}

void ASEGameMode::ChangeFloor(uint8 InFloor)
{
	if (const struct FSoftWorldReference* Findee = FloorToLevel.Find(InFloor))
	{
		ChangeFloor(*Findee);
	}
}

class USESaveGame* ASEGameMode::GetSaveGame() const
{
	if (SaveGame == nullptr)
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveIndex))
		{
			SaveGame = Cast<USESaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveIndex));
		}

		if (SaveGame == nullptr)
		{
			SaveGame = Cast<USESaveGame>(UGameplayStatics::CreateSaveGameObject(USESaveGame::StaticClass()));
			SaveGame->SetFloorState(StartingFloor, true);
		}
	}

	check(SaveGame != nullptr);

	return SaveGame;
}

void ASEGameMode::Save()
{
	if (SaveGame)
	{
		UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlot, SaveIndex);
	}
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
	if (ASEGameState* GS = GetGameState<ASEGameState>())
	{
		GS->Multicast_OpenElevator();
	}
}