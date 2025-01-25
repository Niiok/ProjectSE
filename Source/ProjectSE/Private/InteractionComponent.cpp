// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "SECharacter.h"



const FName UInteractionComponent::HoldSocket = TEXT("hand_r");

void UInteractionComponent::Interact(class ASECharacter* InInteractor)
{
	if (IsValid(this))
	{
		OnInteract.Broadcast(InInteractor);
	}
}

void UInteractionComponent::Hold(class ASECharacter* InHolder)
{
	if (IsValid(this))
	{
		OnHold.Broadcast(InHolder);
	}

	if (auto MeshComponent = InHolder ? InHolder->GetMesh() : nullptr)
	{
		FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
		AttachToComponent(MeshComponent, AttachRule, HoldSocket);
	}
}

void UInteractionComponent::UnHold(class ASECharacter* InUnHolder)
{
	if (IsValid(this))
	{
		OnUnhold.Broadcast(InUnHolder);
	}

	FDetachmentTransformRules DetachRule(EDetachmentRule::KeepWorld, true);
	DetachFromComponent(DetachRule);
}

void UInteractionComponent::Use(class ASECharacter* InUser)
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