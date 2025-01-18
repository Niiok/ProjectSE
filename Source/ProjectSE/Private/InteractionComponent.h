// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "InteractionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentOnInteractSignature, UInteractionComponent, OnInteract, class ASECharacter*, InCharacter);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentOnHoldSignature, UInteractionComponent, OnHold, class ASECharacter*, InCharacter);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentOnUnholdSignature, UInteractionComponent, OnUnhold, class ASECharacter*, InCharacter);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentOnUseSignature, UInteractionComponent, OnUse, class ASECharacter*, InCharacter);

/**
 * 
 */
UCLASS()
class UInteractionComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	virtual bool IsInteractable(class ASECharacter* InCharacter) const { return true; }
	virtual bool IsHoldable(class ASECharacter* InCharacter) const { return false; }
	virtual bool IsUnholdable(class ASECharacter* InCharacter) const { return false; }
	virtual bool IsUsable(class ASECharacter* InCharacter) const { return false; }

	virtual void Interact(class ASECharacter* InCharacter);
	virtual void Hold(class ASECharacter* InCharacter);
	virtual void Unhold(class ASECharacter* InCharacter);
	virtual void Use(class ASECharacter* InCharacter);

	virtual void OnFocusedIn(class ASEPlayerController* InPlayerController);
	virtual void OnFocusedOut(class ASEPlayerController* InPlayerController);


public:
	UPROPERTY(BlueprintAssignable)
	FComponentOnInteractSignature OnInteract;
	UPROPERTY(BlueprintAssignable)
	FComponentOnHoldSignature OnHold;
	UPROPERTY(BlueprintAssignable)
	FComponentOnUnholdSignature OnUnhold;
	UPROPERTY(BlueprintAssignable)
	FComponentOnUseSignature OnUse;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* IdleOverlayMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* FocusedOverlayMaterial;
};
