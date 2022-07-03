#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "DataComponent.h"
#include "../PartyManager/Inventory.h"
#include "../Data/ItemData.h"

#include "CraftableComponent.generated.h"

/***************************************************************************************
Title:       CraftableComponent
Author:      Joshua Griffis
Date:        2022/06/08
Description: Tells the game that the item with this component can be crafted using the materials listed.
*****************************************************************************************/

USTRUCT(BlueprintType)
struct FCraftingMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "99"))
		uint8 amount = 0;

};

UCLASS(BlueprintType, Blueprintable)
class PROJECT_API UCraftableComponent : public UDataComponent
{
	GENERATED_BODY()

public:

	static const FString GetStaticType() { return "UCraftableComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

public:

	UCraftableComponent();


protected:

	UPROPERTY(EditAnywhere, BlueprintType, Blueprintable)
		TArray<FCraftingMaterial> Ingredients;

public:

	TArray<FCraftingMaterial> GetMaterials() { return Ingredients; }

};


