// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "SECharacter.h"
#include "SEGameState.h"




void UInteractionComponent::Auth_Interact(class ASECharacter* InInteractor)
{
	if (IsValid(this))
	{
		OnInteract.Broadcast(InInteractor);
	}
}

void UInteractionComponent::Auth_Hold(class ASECharacter* InHolder)
{
	if (IsValid(this))
	{
		OnHold.Broadcast(InHolder);
	}

	if (InHolder)
	{
		InHolder->Auth_SetCurrentHolding(this);
	}
}

void UInteractionComponent::Auth_UnHold(class ASECharacter* InUnHolder)
{
	if (IsValid(this))
	{
		OnUnhold.Broadcast(InUnHolder);
	}

	if (InUnHolder && InUnHolder->GetHoldingComponent() == this)
	{
		InUnHolder->Auth_SetCurrentHolding(nullptr);
	}
}

void UInteractionComponent::Auth_Use(class ASECharacter* InUser)
{
	if (IsValid(this))
	{
		OnUse.Broadcast(InUser);
	}
}

void UInteractionComponent::OnFocusedIn(class ASEPlayerController* InPlayerController)
{
	SetOverlayMaterial(FocusedOverlayMaterial);
}

void UInteractionComponent::OnFocusedOut(class ASEPlayerController* InPlayerController)
{
	SetOverlayMaterial(IdleOverlayMaterial);
}