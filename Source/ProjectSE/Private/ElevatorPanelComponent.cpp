// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPanelComponent.h"

#include "ElevatorButtonComponent.h"
#include "SECharacter.h"
#include "SEPlayerController.h"




bool UElevatorPanelComponent::IsInteractable(class ASECharacter* InInteractor) const
{
	if (UInteractionComponent* Holding = InInteractor ? InInteractor->GetHolding() : nullptr)
	{
		return Holding->IsA<UElevatorButtonComponent>();
	}
	return false;
}

void UElevatorPanelComponent::Interact(class ASECharacter* InInteractor)
{
	Super::Interact(InInteractor);

	ASEPlayerController* PC = InInteractor ? InInteractor->GetController<ASEPlayerController>() : nullptr;
	UElevatorButtonComponent* Button = InInteractor ? Cast<UElevatorButtonComponent>(InInteractor->GetHolding()) : nullptr;

	if (PC && Button)
	{
		PC->ServerSetFloorState(Button->GetFloorNumber(), true);
	}
}
