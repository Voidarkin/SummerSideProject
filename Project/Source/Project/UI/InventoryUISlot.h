#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUISlot.generated.h"

/***************************************************************************************
Title:       InventorySlotUI
Author:      Joshua Griffis
Date:        2022/07/29
Description: Displays Inventory slot list item
*****************************************************************************************/

class UButton;
class UTextBlock;
class UInventoryUI;

UCLASS()
class PROJECT_API UInventoryUISlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		UButton* SlotButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Name;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Amount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInventoryUI* InventoryUI;

public:
	UFUNCTION()
		void SetItemFields(FText name, FText amount);
	UFUNCTION()
		void OnButtonClicked();
	UFUNCTION()
		void OnButtonHovered();
	UFUNCTION()
		void SetLinkedUI(UInventoryUI* UI);

	virtual void NativeConstruct() override;

protected:
	virtual bool Initialize() override;

};
