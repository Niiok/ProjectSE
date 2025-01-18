// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"




void UInteractionComponent::Interact(class ASECharacter* InCharacter)
{
	if (IsValid(this))
	{
		OnInteract.Broadcast(InCharacter);
	}
}

void UInteractionComponent::Hold(class ASECharacter* InCharacter)
{
	if (IsValid(this))
	{
		OnHold.Broadcast(InCharacter);
	}
}

void UInteractionComponent::Unhold(class ASECharacter* InCharacter)
{
	if (IsValid(this))
	{
		OnUnhold.Broadcast(InCharacter);
	}
}

void UInteractionComponent::Use(class ASECharacter* InCharacter)
{
	if (IsValid(this))
	{
		OnUse.Broadcast(InCharacter);
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