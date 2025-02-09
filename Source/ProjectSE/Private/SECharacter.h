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

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	class UInteractionComponent* GetFocusingComponent() const;
	class UInteractionComponent* GetHoldingComponent() const { return CurrentHolding; }

	UFUNCTION(BlueprintCallable)
	void TryInteract();
	UFUNCTION(BlueprintCallable)
	void TryHoldOrUnhold();
	UFUNCTION(BlueprintCallable)
	void TryUse();

	UFUNCTION(Server, Unreliable)
	void Server_Interact(class UInteractionComponent* InComponent);
	UFUNCTION(Server, Unreliable)
	void Server_Hold(class UInteractionComponent* InComponent);
	UFUNCTION(Server, Unreliable)
	void Server_UnHold(class UInteractionComponent* InComponent);
	UFUNCTION(Server, Unreliable)
	void Server_Use(class UInteractionComponent* InComponent);

	void Auth_SetCurrentHolding(class UInteractionComponent* InComonent);

protected:
	UFUNCTION()
	void OnRep_CurrentHolding(class UInteractionComponent* CurrentHolding_Old);


protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHolding)
	class UInteractionComponent* CurrentHolding;
};
