// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "InteractComponent.generated.h"

/**
 * 
 */
UCLASS()
class UInteractComponent : public UStaticMeshComponent
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BeginCursorOver_Interanl(class UPrimitiveComponent* InComponent);
	UFUNCTION()
	virtual void EndCursorOver_Interanl(class UPrimitiveComponent* InComponent);
	UFUNCTION()
	virtual void OnClicked_Internal(class UPrimitiveComponent* InComponent, FKey InKey);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* IdleOverlayMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* FocusedOverlayMaterial;
};
