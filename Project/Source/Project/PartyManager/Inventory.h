#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

/***************************************************************************************
Title:       Inventory
Author:      Joshua Griffis
Date:        2022/06/12
Description: The stored information on what the player owns
*****************************************************************************************/

USTRUCT(BlueprintType)
struct FInventorySlot
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "99"))
		int amount = 0;

};

class UItemData;

UCLASS()
class PROJECT_API UInventory : public UObject
{
	GENERATED_BODY()
	
public:

	UInventory();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventorySlot> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "9999"))
		int money;

public:

	void AddItem(FString name, int amount);
	void RemoveItem(FString name, int amount);
	void IncreaseMoney(int amount);
	void DecreaseMoney(int amount);
	int GetMoney() { return money; }
	TArray<FInventorySlot> GetInventory() { return Inventory; }

	bool CheckIfHasItem(FString itemName);
	bool CheckIfHasItem(FString itemName, int itemAmount);

	void UseItem(UItemData* item, class UCharacterData* character);
	//void UseItem(Battler* battler);

protected:


};
