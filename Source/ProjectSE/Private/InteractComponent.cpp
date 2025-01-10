// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnBeginCursorOver.AddUniqueDynamic(this, &UInteractComponent::BeginCursorOver_Interanl);
	OnEndCursorOver.AddUniqueDynamic(this, &UInteractComponent::EndCursorOver_Interanl);
	OnClicked.AddUniqueDynamic(this, &UInteractComponent::OnClicked_Internal);
}

void UInteractComponent::BeginCursorOver_Interanl(class UPrimitiveComponent* InComponent)
{
	SetOverlayMaterial(FocusedOverlayMaterial);
}

void UInteractComponent::EndCursorOver_Interanl(class UPrimitiveComponent* InComponent)
{
	SetOverlayMaterial(IdleOverlayMaterial);
}

void UInteractComponent::OnClicked_Internal(class UPrimitiveComponent* InComponent, FKey InKey)
{
}
