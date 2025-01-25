// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorButtonComponent.h"

#include "Components/TextRenderComponent.h"
#include "Elevator.h"
#include "SECharacter.h"
#include "SEGameState.h"
#include "SEPlayerController.h"




void UElevatorButtonComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	
	if (AActor* Owner = GetOwner())
	{
		NumberComponent = Cast<UTextRenderComponent>(GetOwner()->AddComponentByClass(UTextRenderComponent::StaticClass(), false, NumberTransform, false));
		if (Owner->GetRootComponent() == NumberComponent)
		{
			Owner->SetRootComponent(this);
		}
		NumberComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		NumberComponent->SetText(FText::AsNumber(FloorNumber));
		NumberComponent->SetHorizontalAlignment(EHTA_Center);
		NumberComponent->SetVerticalAlignment(EVRTA_TextCenter);
		NumberComponent->SetWorldSize(NumberSize);
	}
}

void UElevatorButtonComponent::Interact(class ASECharacter* InInteractor)
{
	Super::Interact(InInteractor);

	if (ASEPlayerController* PC = InInteractor ? InInteractor->GetController<ASEPlayerController>() : nullptr)
	{
		PC->ServerChangeFloor(FloorNumber);
	}
}

void UElevatorButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	bIsDropped = GetTypedOuter<AElevator>() == nullptr;

	ASEGameState* GS = GetWorld()->GetGameState<ASEGameState>();
	GS->OnFloorStateChanged.AddUObject(this, &UElevatorButtonComponent::OnFloorStateChanged);
	OnFloorStateChanged(FloorNumber, GS && GS->IsFloorOpened(FloorNumber));
}

void UElevatorButtonComponent::OnFloorStateChanged(uint8 InFloor, bool bIsOpened)
{
	if (InFloor == FloorNumber)
	{
		bIsFloorOpened = bIsOpened;

		if (bIsDropped == false)
		{
			SetVisibility(bIsFloorOpened);
		}
		else if (bIsDropped && bIsFloorOpened)
		{
			GetOwner()->Destroy();
		}
	}
}
