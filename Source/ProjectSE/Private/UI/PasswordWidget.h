// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PasswordWidget.generated.h"


/**
 * 
 */
UCLASS()
class UPasswordWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Enter(int32 InPassword);
	UFUNCTION(BlueprintCallable)
	void Reset();

	int32 GetFirstBlankIndex() const;
	int32 GetLastNumberIndex() const;
	int32 GetPassword() const;

	void RefreshTexts();
	void InputNumber(char InNumber);
	void Backspace();
	void TryEnter();


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_1000;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_0100;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_0010;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_0001;

	class UTextBlock** TextBlockNumbers[4] = { &TextBlock_1000, &TextBlock_0100, &TextBlock_0010, &TextBlock_0001 };

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number0;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number2;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number3;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number4;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number5;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number6;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number7;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number8;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Number9;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Backspace;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USEButton* Button_Enter;

	class USEButton** ButtonNumbers[10] = {
	&Button_Number0, &Button_Number1, &Button_Number2, &Button_Number3, &Button_Number4,
	&Button_Number5, &Button_Number6, &Button_Number7, &Button_Number8, &Button_Number9 };

	char Numbers[4]{ INDEX_NONE, INDEX_NONE, INDEX_NONE, INDEX_NONE };
};
