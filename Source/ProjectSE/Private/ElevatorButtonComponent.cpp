// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorButtonComponent.h"

#include "Components/TextRenderComponent.h"
#include "Elevator.h"
#include "SECharacter.h"
#include "SEGameMode.h"
#include "SEGameState.h"




void UElevatorButtonComponent::Auth_Interact(class ASECharacter* InInteractor)
{
	Super::Auth_Interact(InInteractor);

	if (ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>())
	{
		GM->ChangeFloor(FloorNumber);
	}
}

void UElevatorButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	bIsDropped = GetTypedOuter<AElevator>() == nullptr;

	ASEGameState* GS = GetWorld()->GetGameState<ASEGameState>();
	GS->OnFloorStateChanged.AddUObject(this, &UElevatorButtonComponent::OnFloorStateChanged);
	OnFloorStateChanged(FloorNumber, GS && GS->IsFloorOpened(FloorNumber));
}

void UElevatorButtonComponent::OnFloorStateChanged(uint8 InFloor, bool bIsOpened)
{
	if (InFloor == FloorNumber)
	{
		bIsFloorOpened = bIsOpened;

		if (bIsDropped == false)
		{
			SetVisibility(bIsFloorOpened);
		}
		else if (bIsDropped && bIsFloorOpened)
		{
			GetOwner()->Destroy();
		}

		AdjustText();
	}
}

void UElevatorButtonComponent::AdjustText()
{
	UTextRenderComponent* NumberComponent;
	if (GetAttachChildren().FindItemByClass<UTextRenderComponent>(&NumberComponent))
	{
		NumberComponent->SetText(FText::AsNumber(FloorNumber));
		NumberComponent->SetHorizontalAlignment(EHTA_Center);
		NumberComponent->SetVerticalAlignment(EVRTA_TextCenter);
		NumberComponent->SetVisibility(GetVisibleFlag());
	}
}
