// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/StatefulInteractionComponent.h"
#include "LockInteractionComponent.generated.h"


/**
 * 
 */
UCLASS()
class ULockInteractionComponent : public UStatefulInteractionComponent
{
	GENERATED_BODY()

protected:
	enum
	{
		State_Closed = 0,
		State_Opened = 1,
	};

public:
	virtual bool IsInteractable(class ASECharacter* InInteractor) const override;
};


/**
 * 
 */
UCLASS()
class ULockInteractionComponent_Holding : public ULockInteractionComponent
{
	GENERATED_BODY()

public:
	enum
	{
		Param_NoHolding = 1,
		Param_NotCorrectClass = 2,
		Param_NotCorrectObject = 3,
		Param_NoUnlockMethod = 4,
	};

protected:
	virtual int64 Auth_Interact(class ASECharacter* InInteractor, int64 InParam) override;
	virtual int64 Local_Interact(class ASECharacter* InInteractor, int64 InParam) override;
	virtual void OnRep_State(int64 OldState) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInteractionComponent> UnlockClass;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UInteractionComponent> UnlockObject;

	UPROPERTY(EditAnywhere)
	bool bDestoryUnlockObject = true;
};


/**
 * 
 */
UCLASS()
class ULockInteractionComponent_Password : public ULockInteractionComponent
{
	GENERATED_BODY()
	
public:
	enum
	{
		Param_OpenDialogue = 1,
		Param_WrongPassword = 2,
		Param_NoPassword = 3,
	};

	static int64 OffsetPassword(int64 InPassword);
	static uint32 EncryptPassword(int64 InPassword);

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual int64 Auth_Interact(class ASECharacter* InInteractor, int64 InParam) override;
	virtual int64 Local_Interact(class ASECharacter* InInteractor, int64 InParam) override;

public:
	bool HasPassword() const { return UnlockHash != 0; }

	UFUNCTION(BlueprintImplementableEvent)
	void OpenPasswordWidget(class ASECharacter* InCharacter);
	UFUNCTION(BlueprintCallable)
	void TryPassword(class ASECharacter* InCharacter, int64 InPassword);

protected:
	UPROPERTY(VisibleAnywhere)
	uint32 UnlockHash = 0;
	UPROPERTY(EditAnywhere, Transient, meta = (UIMin = "0", UIMax = "9999"))
	int32 UnlockPassword = INDEX_NONE;
};