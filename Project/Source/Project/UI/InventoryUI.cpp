#include "InventoryUI.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "InventoryUISlot.h"
#include "../PartyManager/Inventory.h"
#include "../PartyManager/PartyManager.h"
#include "../Data/DatabaseManager.h"
#include "../Data/ItemDatabase.h"
#include "../Data/ItemData.h"

void UInventoryUI::SetInventorySlots()
{
	VerticalBox_Inventory->ClearChildren();

	UPartyManager* PartyManager = GetGameInstance()->GetSubsystem<UPartyManager>();
	UInventory* Inventory = PartyManager->GetInventory();

	for (FInventorySlot slot : Inventory->GetInventory())
	{
		UInventoryUISlot* InventoryEntry = CreateWidget<UInventoryUISlot>(VerticalBox_Inventory, InventorySlotClass);
		FText name = FText::FromString(slot.name);
		FText amount = FText::AsNumber(slot.amount);
		InventoryEntry->SetItemFields(name, amount);
		InventoryEntry->SetLinkedUI(this);
		if (InventoryEntry->SlotButton) { InventoryEntry->SlotButton->OnClicked.AddDynamic(InventoryEntry, &UInventoryUISlot::OnButtonClicked); }
		VerticalBox_Inventory->AddChildToVerticalBox(InventoryEntry);
	}

	UDatabaseManager* DatabaseManager = GetGameInstance()->GetSubsystem<UDatabaseManager>();
	FString itemName = (Cast<UInventoryUISlot>(VerticalBox_Inventory->GetChildAt(0))->Text_Name->Text).ToString();
	
	SetSelectedItem(FText::FromString(itemName));

	//VerticalBox_Inventory->GetChildAt(0)->SetFocus();
	
}

void UInventoryUI::SetItemInfo(FText Info)
{
	Text_Info->SetText(Info);
}

void UInventoryUI::SetSelectedItem(FText Item)
{
	SelectedItem = nullptr;
	UDatabaseManager* DatabaseManager = GetGameInstance()->GetSubsystem<UDatabaseManager>();
	FString itemName = Item.ToString();
	SelectedItem = DatabaseManager->GetItemDatabase()->GetItem(itemName);

	SetItemInfo(FText::FromString(SelectedItem->GetItemDescription()));
}

bool UInventoryUI::Initialize()
{
	bool bResult = Super::Initialize();
	if (!bResult)
	{
		return false;
	}

	static ConstructorHelpers::FClassFinder<UInventoryUISlot> InventoryUISlotBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/UI/WBP_InventorySlot"));
	if (InventoryUISlotBPClass.Class != NULL)
	{
		InventorySlotClass = InventoryUISlotBPClass.Class;
	}

	return bResult;
}