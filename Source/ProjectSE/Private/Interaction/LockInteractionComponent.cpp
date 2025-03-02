// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/LockInteractionComponent.h"
#include "Misc/MessageDialog.h"
#include "SECharacter.h"
#include "SEGameMode.h"




bool ULockInteractionComponent::IsInteractable(class ASECharacter* InInteractor) const
{
	return GetState() == State_Closed;
}




int64 ULockInteractionComponent_Holding::Auth_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	Super::Auth_Interact(InInteractor, InParam);

	if (UInteractionComponent* Holding = InInteractor->GetHoldingComponent())
	{
		ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>();

		if (UnlockClass)
		{
			bool bCorrect = Holding->GetClass()->IsChildOf(UnlockClass);
			if (bCorrect && IsValid(GM))
			{
				GM->SetInteractionState(this, State_Opened);
				// since there's no specific object path, destroy current holding actor
				if (bDestoryUnlockObject && IsValid(Holding->GetOwner()))
				{
					Holding->GetOwner()->Destroy();
				}
			}
		 	return bCorrect	? Param_End : Param_NotCorrectClass;
		}
		else if (UnlockObject)
		{
			bool bCorrect = Holding == UnlockObject;
			if (bCorrect && IsValid(GM))
			{
				GM->SetInteractionState(this, State_Opened);
			}
			return bCorrect	? Param_End : Param_NotCorrectObject;
		}
	}
	else
	{
		return Param_NoHolding;
	}
	return Param_NoUnlockMethod;
}

int64 ULockInteractionComponent_Holding::Local_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	switch (InParam)
	{
	case Param_NoHolding:
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("no holding object")));
		break;
	case Param_NotCorrectClass:
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("not correct class")));
		break;
	case Param_NotCorrectObject:
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("not correct object")));
		break;
	case Param_NoUnlockMethod:
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("no way to open")));
		break;
	default:
		break;
	}

	return Super::Local_Interact(InInteractor, InParam);
}

void ULockInteractionComponent_Holding::OnRep_State(int64 OldState)
{
	Super::OnRep_State(OldState);

	if (State != State_Opened)
	{
		return;
	}

	if (UInteractionComponent* Unlocker = UnlockObject.Get())
	{
		if (IsValid(Unlocker) && IsValid(Unlocker->GetOwner()))
		{
			Unlocker->GetOwner()->Destroy();
		}
	}
}




int64 ULockInteractionComponent_Password::OffsetPassword(int64 InPassword)
{
	return InPassword + 100;
}

uint32 ULockInteractionComponent_Password::EncryptPassword(int64 InPassword)
{
	return GetTypeHash(InPassword + 100);
}

#if WITH_EDITOR
void ULockInteractionComponent_Password::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	static const FName NAME_UnlockPassword = GET_MEMBER_NAME_CHECKED(ULockInteractionComponent_Password, UnlockPassword);

	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetName() == NAME_UnlockPassword)
	{
		UnlockHash = UnlockPassword != INDEX_NONE ? EncryptPassword(OffsetPassword(UnlockPassword)) : 0;
		Modify();
	}
}
#endif

int64 ULockInteractionComponent_Password::Auth_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	Super::Auth_Interact(InInteractor, InParam);

	if (HasPassword())
	{
		if (InParam == Param_Start)
		{
			return Param_OpenDialogue;
		}

		ASEGameMode* GM = GetWorld()->GetAuthGameMode<ASEGameMode>();
		bool bCorrect = EncryptPassword(InParam) == UnlockHash;
		if (bCorrect && IsValid(GM))
		{
			GM->SetInteractionState(this, State_Opened);
		}
		return bCorrect ? Param_End : Param_WrongPassword;
	}
	return Param_NoPassword;
}

int64 ULockInteractionComponent_Password::Local_Interact(class ASECharacter* InInteractor, int64 InParam)
{
	switch (InParam)
	{
	case Param_OpenDialogue:
		OpenPasswordWidget(InInteractor);
		break;
	case Param_WrongPassword:
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("wrong password")));
		break;
	case Param_NoPassword:
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("no way to open")));
		break;
	default:
		break;
	}

	return Super::Local_Interact(InInteractor, InParam);
}

void ULockInteractionComponent_Password::TryPassword(class ASECharacter* InCharacter, int64 InPassword)
{
	if (IsValid(this) && IsValid(InCharacter))
	{
		InCharacter->Server_Interact(this, OffsetPassword(InPassword));
	}
}
