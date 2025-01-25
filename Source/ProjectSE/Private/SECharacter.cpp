// Fill out your copyright notice in the Description page of Project Settings.


#include "SECharacter.h"

#include "InteractionComponent.h"
#include "SEPlayerController.h"


// Sets default values
ASECharacter::ASECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASECharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


class UInteractionComponent* ASECharacter::GetFocusingComponent() const
{
	ASEPlayerController* PC = GetController<ASEPlayerController>();

	return PC ? PC->GetFocusingInteraction() : nullptr;
}

void ASECharacter::TryInteract()
{
	UInteractionComponent* Focusing = GetFocusingComponent();

	if (Focusing && Focusing->IsInteractable(this))
	{
		Focusing->Interact(this);
	}
}

void ASECharacter::TryHoldOrUnhold()
{
	if (CurrentHolding.IsValid())
	{
		UnHold();
	}
	else
	{
		Hold(GetFocusingComponent());
	}
}

void ASECharacter::TryUse()
{
	if (CurrentHolding.IsValid() && CurrentHolding->IsUsable(this))
	{
		CurrentHolding->Use(this);
	}
}

bool ASECharacter::Hold(class UInteractionComponent* InComponent)
{
	if (InComponent && InComponent->IsHoldable(this))
	{
		InComponent->Hold(this);
		CurrentHolding = InComponent;
		return true;
	}
	return false;
}

bool ASECharacter::UnHold()
{
	if (CurrentHolding.IsValid() && CurrentHolding->IsUnholdable(this))
	{
		CurrentHolding->UnHold(this);
		CurrentHolding.Reset();
		return true;
	}
	return false;
}
