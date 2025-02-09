// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPanelComponent.h"

#include "ElevatorButtonComponent.h"
#include "SECharacter.h"
#include "SEGameMode.h"




bool UElevatorPanelComponent::IsInteractable(class ASECharacter* InInteractor) const
{
	if (UInteractionComponent* Holding = InInteractor ? InInteractor->GetHoldingComponent() : nullptr)
	{
		return Holding->IsA<UElevatorButtonComponent>();
	}
	return false;
}

int64 UElevatorPanelComponent::Auth_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	Super::Auth_Interact(InInteractor, InParam);
	
	ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>();
	UElevatorButtonComponent* Button = InInteractor ? Cast<UElevatorButtonComponent>(InInteractor->GetHoldingComponent()) : nullptr;

	if (GM && Button)
	{
		GM->SetFloorState(Button->GetFloorNumber(), true);
	}

	return Param_End;
}
