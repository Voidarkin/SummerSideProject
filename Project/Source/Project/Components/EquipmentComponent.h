// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "DataComponent.h"

#include "EquipmentComponent.generated.h"

/***************************************************************************************
Title:       EquipmentComponent
Author:      Joshua Griffis
Date:        2022/06/08
Description: Determines if an item is a piece of equipment
*****************************************************************************************/

UCLASS(BlueprintType)
class PROJECT_API UEquipmentComponent : public UDataComponent
{
	GENERATED_BODY()

public:

	static const FString GetStaticType() { return "UEquipmentComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipSlot Slot;

	UFUNCTION()
		EEquipSlot GetSlot() { return Slot; }

};
