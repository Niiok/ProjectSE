// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "SEButton.generated.h"


/**
 * 
 */
UCLASS()
class USEButton : public UButton
{
	GENERATED_BODY()


protected:
	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void OnClickedNonDynamic_Interanl() { OnClickedNonDynamic.Broadcast(); }


public:
	FSimpleMulticastDelegate OnClickedNonDynamic;
};
