// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PasswordWidget.h"
#include "Components/TextBlock.h"
#include "SEButton.h"


void UPasswordWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TWeakObjectPtr<UPasswordWidget> WeakThis(this);
	
	for (int32 i = 0; i < UE_ARRAY_COUNT(ButtonNumbers); ++i)
	{
		USEButton* Button = *ButtonNumbers[i];

		Button->OnClickedNonDynamic.AddLambda(
			[WeakThis, i]() {
				if (WeakThis.IsValid())
				{
					WeakThis->InputNumber(i);
				}
			});
	}

	Button_Backspace->OnClickedNonDynamic.AddUObject(this, &UPasswordWidget::Backspace);

	Button_Enter->OnClickedNonDynamic.AddUObject(this, &UPasswordWidget::TryEnter);

	RefreshTexts();
}

void UPasswordWidget::Reset()
{
	for (auto& ele : Numbers)
	{
		ele = INDEX_NONE;
	}

	RefreshTexts();
}

int32 UPasswordWidget::GetFirstBlankIndex() const
{
	int32 Index = 0;
	for (; Index < UE_ARRAY_COUNT(Numbers); ++Index)
	{
		if (Numbers[Index] < 0)
		{
			return Index;
		}
	}

	return INDEX_NONE;
}


int32 UPasswordWidget::GetLastNumberIndex() const
{
	int32 Index = 0;
	for (; Index < UE_ARRAY_COUNT(Numbers); ++Index)
	{
		if (Numbers[Index] < 0)
		{
			break;
		}
	}

	return Index - 1;
}

int32 UPasswordWidget::GetPassword() const
{
	if (GetFirstBlankIndex() == INDEX_NONE)
	{
		int32 Password = 0;
		Password += Numbers[0] * 1000;
		Password += Numbers[1] * 100;
		Password += Numbers[2] * 10;
		Password += Numbers[3];
		return Password;
	}
	else
	{
		return INDEX_NONE;
	}
}


void UPasswordWidget::RefreshTexts()
{
	check(UE_ARRAY_COUNT(Numbers) == UE_ARRAY_COUNT(TextBlockNumbers));

	int32 Index = 0;
	for (; Index < UE_ARRAY_COUNT(Numbers); ++Index)
	{
		UTextBlock* Txt = *TextBlockNumbers[Index];
		int32 Number = Numbers[Index];
		Txt->SetText(FMath::IsWithinInclusive(Number, 0, 9) ? FText::AsNumber(Number) : FText::GetEmpty());
	}
}

void UPasswordWidget::InputNumber(char InNumber)
{
	int32 Index = GetFirstBlankIndex();

	if (Index > INDEX_NONE)
	{
		Numbers[Index] = InNumber;
		RefreshTexts();
	}
}

void UPasswordWidget::Backspace()
{
	int32 Index = GetLastNumberIndex();

	if (Index > INDEX_NONE)
	{
		Numbers[Index] = INDEX_NONE;
		RefreshTexts();
	}
}

void UPasswordWidget::TryEnter()
{
	int32 Password = GetPassword();

	if (Password > INDEX_NONE)
	{
		Enter(Password);
	}
}