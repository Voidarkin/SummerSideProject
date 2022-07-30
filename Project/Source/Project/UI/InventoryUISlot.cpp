#include "InventoryUISlot.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "InventoryUI.h"

void UInventoryUISlot::SetItemFields(FText name, FText amount)
{
	Text_Name->SetText(name);
	Text_Amount->SetText(amount);
}

void UInventoryUISlot::OnButtonClicked()
{
	//Menu->SetItemInfo(Text_Name->Text.ToString()); //Causing errors
}
void UInventoryUISlot::OnButtonHovered()
{
	InventoryUI->SetSelectedItem(Text_Name->Text);
}

void UInventoryUISlot::SetLinkedUI(UInventoryUI* UI)
{
	InventoryUI = UI;
}

void UInventoryUISlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UInventoryUISlot::OnButtonClicked);

		SlotButton->OnHovered.AddDynamic(this, &UInventoryUISlot::OnButtonHovered);
		//SlotButton->OnHovered.AddDynamic(InventoryUI, &UInventoryUI::SetSelectedItem(Text_Name->Text));
	}
}

bool UInventoryUISlot::Initialize()
{
	bool bResult = Super::Initialize();
	if (!bResult)
	{
		return false;
	}



	return bResult;
}