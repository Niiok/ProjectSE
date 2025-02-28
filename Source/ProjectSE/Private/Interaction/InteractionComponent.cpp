// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "SECharacter.h"
#include "SEGameState.h"




int64 UInteractionComponent::Auth_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	if (IsValid(this))
	{
		Auth_OnInteract.Broadcast(InInteractor, InParam);
	}

	return Param_End;
}

int64 UInteractionComponent::Local_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	if (IsValid(this))
	{
		Local_OnInteract.Broadcast(InInteractor, InParam);
	}

	return Param_Null;
}

void UInteractionComponent::Auth_Hold(class ASECharacter* InHolder)
{
	if (InHolder)
	{
		InHolder->Auth_SetCurrentHolding(this);
	}
}

void UInteractionComponent::Auth_UnHold(class ASECharacter* InUnHolder)
{
	if (InUnHolder && InUnHolder->GetHoldingComponent() == this)
	{
		InUnHolder->Auth_SetCurrentHolding(nullptr);
	}
}

void UInteractionComponent::Auth_Use(class ASECharacter* InUser)
{
	if (IsValid(this))
	{
		Auth_OnUse.Broadcast(InUser);
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