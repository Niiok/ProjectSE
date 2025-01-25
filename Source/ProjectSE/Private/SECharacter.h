// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SECharacter.generated.h"

UCLASS()
class ASECharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	ASECharacter();

protected:
	virtual void BeginPlay() override;

	
public:
	class UInteractionComponent* GetFocusingComponent() const;

	UFUNCTION(BlueprintCallable)
	void TryInteract();
	
	UFUNCTION(BlueprintCallable)
	void TryHoldOrUnhold();
	
	UFUNCTION(BlueprintCallable)
	void TryUse();

	class UInteractionComponent* GetHolding() const { return CurrentHolding.Get(); }
	bool Hold(class UInteractionComponent* InComponent);
	bool UnHold();

protected:
	TWeakObjectPtr<class UInteractionComponent> CurrentHolding;
};
