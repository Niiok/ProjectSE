// Fill out your copyright notice in the Description page of Project Settings.


#include "SEPlayerController.h"




ASEPlayerController::ASEPlayerController()
{
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ASEPlayerController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	if (bShowMouseCursor == false)
	{
		int32 SizeX, SizeY;
		GetViewportSize(SizeX, SizeY);
		SetMouseLocation(SizeX * 0.5f, SizeY * 0.5f);
	}

	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
}
