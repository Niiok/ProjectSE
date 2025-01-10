// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

#include "SEGameMode.h"


// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	if (ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>())
	{
		GM->RegisterElevator(this);
	}
}

