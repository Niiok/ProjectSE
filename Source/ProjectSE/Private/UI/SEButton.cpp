// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SEButton.h"




void USEButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	
	OnClicked.AddUniqueDynamic(this, &USEButton::OnClickedNonDynamic_Interanl);
}
