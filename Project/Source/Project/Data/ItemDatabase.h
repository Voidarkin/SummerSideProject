#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Engine/DataAsset.h"

#include "ItemDatabase.generated.h"

/***************************************************************************************
Title:       ItemDatabase
Author:      Joshua Griffis
Date:        2022/06/12
Description: Stores all the items in an array to be referenced
*****************************************************************************************/

class UItemData;

UCLASS()
class PROJECT_API UItemDatabase : public UObject
{

	GENERATED_BODY()

public:

	UItemDatabase();

	UItemData* GetItem(FString pName);

protected:

	TArray<UItemData*> Database;

	void OnRegistryLoaded();

};
