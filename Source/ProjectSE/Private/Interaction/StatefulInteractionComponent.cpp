// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/StatefulInteractionComponent.h"
#include "Net/UnrealNetwork.h"
#include "SEGameMode.h"




UStatefulInteractionComponent::UStatefulInteractionComponent()
{
	SetIsReplicatedByDefault(true);
}

void UStatefulInteractionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UStatefulInteractionComponent, State);
}

void UStatefulInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>())
	{
		SetState(GM->GetInteractionState(FSoftObjectPath(this)));
	}
}

void UStatefulInteractionComponent::SetState(int64 InState)
{
	int64 OldState = State;
	State = InState;

	if (InState != OldState)
	{
		OnRep_State(OldState);
	}
}

void UStatefulInteractionComponent::OnRep_State(int64 OldState)
{
	OnInteractionStateChanged.Broadcast(State, OldState);
}
