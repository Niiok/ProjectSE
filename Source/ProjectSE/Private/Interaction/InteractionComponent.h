// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "InteractionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FComponentAuthOnInteractSignature, UInteractionComponent, Auth_OnInteract, class ASECharacter*, InCharacter, int64, InParam);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FComponentLocalOnInteractSignature, UInteractionComponent, Local_OnInteract, class ASECharacter*, InCharacter, int64, InParam);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentAuthOnUseSignature, UInteractionComponent, Auth_OnUse, class ASECharacter*, InCharacter);

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UInteractionComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	enum 
	{
		Param_Start = 0,
		Param_End = 0,
		Param_Null = INDEX_NONE
	};

public:
	virtual bool IsInteractable(class ASECharacter* InInteractor) const { return true; }
	virtual bool IsHoldable(class ASECharacter* InHolder) const { return false; }
	virtual bool IsUnHoldable(class ASECharacter* InUnHolder) const { return false; }
	virtual bool IsUsable(class ASECharacter* InUser) const { return false; }

	virtual int64 Auth_Interact(class ASECharacter* InInteractor, int64 InParam);
	virtual int64 Local_Interact(class ASECharacter* InInteractor, int64 InParam);
	virtual void Auth_Hold(class ASECharacter* InHolder);
	virtual void Auth_UnHold(class ASECharacter* InUnHolder);
	virtual void Auth_Use(class ASECharacter* InUser);

	virtual void OnFocusedIn(class ASEPlayerController* InPlayerController);
	virtual void OnFocusedOut(class ASEPlayerController* InPlayerController);


public:
	UPROPERTY(BlueprintAssignable)
	FComponentAuthOnInteractSignature Auth_OnInteract;
	UPROPERTY(BlueprintAssignable)
	FComponentLocalOnInteractSignature Local_OnInteract;
	UPROPERTY(BlueprintAssignable)
	FComponentAuthOnUseSignature Auth_OnUse;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* IdleOverlayMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* FocusedOverlayMaterial;
};
