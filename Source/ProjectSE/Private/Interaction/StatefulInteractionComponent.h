// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionComponent.h"
#include "StatefulInteractionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FComponentOnInteractionStateChangedSignature, UStatefulInteractionComponent, OnInteractionStateChanged, int64, NewState, int64, OldState);

/**
 * 
 */
UCLASS()
class UStatefulInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()
	
protected:
	UStatefulInteractionComponent();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	int64 GetState() const { return State; }
	void SetState(int64 InState);
	bool IsSavingState() const { return bSaveState; }

protected:
	UFUNCTION()
	virtual void OnRep_State(int64 OldState);


public:
	UPROPERTY(BlueprintAssignable)
	FComponentOnInteractionStateChangedSignature OnInteractionStateChanged;

protected:
	UPROPERTY(ReplicatedUsing=OnRep_State)
	int64 State = 0;

	UPROPERTY(EditAnywhere)
	bool bSaveState = true;
};
