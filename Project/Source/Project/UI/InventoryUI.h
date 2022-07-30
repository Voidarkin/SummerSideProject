#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/***************************************************************************************
Title:       InventoryUI
Author:      Joshua Griffis
Date:        2022/07/29
Description: Displays Inventory UI
*****************************************************************************************/

class UBorder;
class UButton;
class UInventoryUISlot;
class UHorizontalBox;
class UTextBlock;
class UVerticalBox;

UCLASS()
class PROJECT_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Inventory;
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Info;
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Party;
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Tabs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UInventoryUISlot> InventorySlotClass;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Info;

	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* HorizontalBox_Tabs;

	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_Party;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_Inventory;

	class UItemData* SelectedItem = nullptr;

public:

	UFUNCTION()
		void SetInventorySlots();
	UFUNCTION()
		void SetItemInfo(FText Info);
	UFUNCTION()
		void SetSelectedItem(FText Item);

protected:

	virtual bool Initialize() override;
};
