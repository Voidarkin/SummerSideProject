#include "Inventory.h"

#include "../Data/ItemData.h"
#include "../Data/CharacterData.h"
#include "../Components/HealthComponent.h"
#include "../Components/StatComponent.h"
#include "../Data/DatabaseManager.h"
#include "../Enums.h"

UInventory::UInventory()
{
	//Default Start
	money = 30;
	AddItem("Potion", 2);
	AddItem("Sword", 1);
}

void UInventory::AddItem(FString name, int amount)
{
	bool bAdded = false;
	if (Inventory.Max() != 0)
	{
		for (int i = 0; i < Inventory.Num(); i++) 
		{
			if (Inventory[i].name == name)
			{
				Inventory[i].amount += amount;
				if (Inventory[i].amount > 99)
				{
					Inventory[i].amount = 99;
				}
				bAdded = true;
			}

		}
		if(!bAdded)
		{
			FInventorySlot slot;
			slot.name = name;
			slot.amount = amount;
			Inventory.Add(slot);
		}
	}
	else
	{
		FInventorySlot slot;
		slot.name = name;
		slot.amount = amount;
		Inventory.Add(slot);
	}
	
	FString debugMessage;
	if (amount > 1)
	{
		debugMessage = FString::Printf(TEXT("You found %d %ss"), amount, *name);
	}
	else
	{
		debugMessage = FString::Printf(TEXT("You found %d %s"), amount, *name);
		
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, debugMessage);
}

void UInventory::RemoveItem(FString name, int amount)
{
	if (Inventory.Num() != 0)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			if (Inventory[i].name == name)
			{
				Inventory[i].amount -= amount;
				if (Inventory[i].amount < 1)
				{
					Inventory.RemoveAt(i);
				}
			}
		}
	}
}

void UInventory::IncreaseMoney(int amount)
{
	money += amount;
	if (money > 9999)
	{
		money = 9999;
	}
}

void UInventory::DecreaseMoney(int amount)
{
	money -= amount;
	if (money < 0)
	{
		money = 0;
	}
}

bool UInventory::CheckIfHasItem(FString itemName)
{
	if (Inventory.Num() != 0)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			if (Inventory[i].name == itemName)
			{
				return true;
			}
		}
	}
	return false;
}

bool UInventory::CheckIfHasItem(FString itemName, int itemAmount)
{
	if (Inventory.Num() != 0)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			if (Inventory[i].name == itemName)
			{
				if (Inventory[i].amount >= itemAmount)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void UInventory::UseItem(UItemData* item, UCharacterData* character)
{

	UHealthComponent* HealthComp = item->GetComponent<UHealthComponent>();
	if (HealthComp)
	{
		int CHP = character->GetCharacterStats()->GetStat("currentHP");
		int MHP = character->GetCharacterStats()->GetStat("maxHP");
		if (HealthComp->GetEffect() == EEffect::Harm)
		{
			CHP -= HealthComp->GetValue();
			if (CHP < 0) { CHP = 0; }
		}
		else if (HealthComp->GetEffect() == EEffect::Heal)
		{
			CHP += HealthComp->GetValue();
			if (CHP > MHP) { CHP = MHP; }
		}
		FString statName = "currentHP";
		character->GetCharacterStats()->SetStat(statName, CHP);
	}

	RemoveItem(item->GetItemName(), 1);
}
