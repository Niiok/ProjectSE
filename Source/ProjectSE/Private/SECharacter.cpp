// Fill out your copyright notice in the Description page of Project Settings.


#include "SECharacter.h"

#include "InteractionComponent.h"
#include "Net/UnrealNetwork.h"
#include "SEPlayerController.h"


// Sets default values
ASECharacter::ASECharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ASECharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASECharacter, CurrentHolding);
}

class UInteractionComponent* ASECharacter::GetFocusingComponent() const
{
	ASEPlayerController* PC = GetController<ASEPlayerController>();

	return PC ? PC->GetFocusingInteraction() : nullptr;
}

void ASECharacter::TryInteract()
{
	UInteractionComponent* CurrentFocusing = GetFocusingComponent();

	if (CurrentFocusing && CurrentFocusing->IsInteractable(this))
	{
		Server_Interact(CurrentFocusing, UInteractionComponent::Param_Start);
	}
}

void ASECharacter::TryHoldOrUnhold()
{
	if (CurrentHolding && CurrentHolding->IsUnHoldable(this))
	{
		Server_UnHold(CurrentHolding);
	}
	else
	{
		UInteractionComponent* CurrentFocusing = GetFocusingComponent();

		if (CurrentFocusing && CurrentFocusing->IsHoldable(this))
		{
			Server_Hold(CurrentFocusing);
		}
	}
}

void ASECharacter::TryUse()
{
	if (CurrentHolding && CurrentHolding->IsUsable(this))
	{
		Server_Use(CurrentHolding);
	}
}

void ASECharacter::Server_Interact_Implementation(class UInteractionComponent* InComponent, int64 InParam)
{
	if (InComponent && InComponent->IsInteractable(this))
	{
		int64 ReturnCode = InComponent->Auth_Interact(this, InParam);
		if (ReturnCode != UInteractionComponent::Param_Null)
		{
			Client_Interact(InComponent, ReturnCode);
		}
	}
}

void ASECharacter::Client_Interact_Implementation(class UInteractionComponent* InComponent, int64 InParam)
{
	if (InComponent && InComponent->IsInteractable(this))
	{
		int64 ReturnCode = InComponent->Local_Interact(this, InParam);
		if (ReturnCode != UInteractionComponent::Param_Null)
		{
			Server_Interact(InComponent, ReturnCode);
		}
	}
}

void ASECharacter::Server_Hold_Implementation(class UInteractionComponent* InComponent)
{
	if (InComponent && InComponent->IsHoldable(this))
	{
		InComponent->Auth_Hold(this);
	}
}

void ASECharacter::Server_UnHold_Implementation(class UInteractionComponent* InComponent)
{
	if (InComponent && InComponent->IsUnHoldable(this))
	{
		InComponent->Auth_UnHold(this);
	}
}

void ASECharacter::Server_Use_Implementation(class UInteractionComponent* InComponent)
{
	if (InComponent && InComponent->IsUsable(this))
	{
		InComponent->Auth_Use(this);
	}
}

void ASECharacter::Auth_SetCurrentHolding(class UInteractionComponent* InComonent)
{
	UInteractionComponent* OldHolding = CurrentHolding;
	CurrentHolding = InComonent;
	OnRep_CurrentHolding(OldHolding);
}

void ASECharacter::OnRep_CurrentHolding(class UInteractionComponent* CurrentHolding_Old)
{
	if (CurrentHolding_Old)
	{
		FDetachmentTransformRules DetachRule(EDetachmentRule::KeepWorld, true);
		CurrentHolding_Old->DetachFromComponent(DetachRule);
	}

	if (CurrentHolding)
	{
		if (auto MeshComponent = GetMesh())
		{
			static const FName HoldSocket = TEXT("hand_r");
			FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
			CurrentHolding->AttachToComponent(MeshComponent, AttachRule, HoldSocket);
		}
	}
}
