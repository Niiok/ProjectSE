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

void UElevatorPanelComponent::Auth_Interact(class ASECharacter* InInteractor)
{
	Super::Auth_Interact(InInteractor);
	
	ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>();
	UElevatorButtonComponent* Button = InInteractor ? Cast<UElevatorButtonComponent>(InInteractor->GetHoldingComponent()) : nullptr;

	if (GM && Button)
	{
		GM->SetFloorState(Button->GetFloorNumber(), true);
	}
}
