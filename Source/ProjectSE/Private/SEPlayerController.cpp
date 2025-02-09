// Fill out your copyright notice in the Description page of Project Settings.


#include "SEPlayerController.h"

#include "InteractionComponent.h"
#include "SECharacter.h"
#include "SEGameMode.h"




void ASEPlayerController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
	
	ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(Player);
	if (LocPlayer && LocPlayer->ViewportClient)
	{
		FVector2D ViewportSize;
		FHitResult HitResult;

		LocPlayer->ViewportClient->GetViewportSize(ViewportSize);
		bool bHit = GetHitResultAtScreenPosition(ViewportSize * 0.5f, ECC_Visibility, true, HitResult);

		UInteractionComponent* NewInteraction = bHit ? Cast<UInteractionComponent>(HitResult.GetComponent()) : nullptr;
		UInteractionComponent* OldInteraction = FocusingInteraction.Get();

		if (NewInteraction != OldInteraction)
		{
			FocusingInteraction = NewInteraction;

			if (OldInteraction)
			{
				OldInteraction->OnFocusedOut(this);
			}

			if (NewInteraction)
			{
				NewInteraction->OnFocusedIn(this);
			}
		}
	}
}