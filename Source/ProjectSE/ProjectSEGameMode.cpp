// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectSEGameMode.h"
#include "ProjectSECharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectSEGameMode::AProjectSEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
