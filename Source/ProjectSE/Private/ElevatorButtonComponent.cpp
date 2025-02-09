// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorButtonComponent.h"

#include "Components/TextRenderComponent.h"
#include "Elevator.h"
#include "SECharacter.h"
#include "SEGameMode.h"
#include "SEGameState.h"




int64 UElevatorButtonComponent::Auth_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	Super::Auth_Interact(InInteractor, InParam);

	if (ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>())
	{
		GM->ChangeFloor(FloorNumber);
	}

	return Param_End;
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

		AdjustText();

		if (bIsDropped == false)
		{
			SetVisibility(bIsFloorOpened);
		}
		else if (bIsDropped && bIsFloorOpened)
		{
			GetOwner()->Destroy();
		}
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
