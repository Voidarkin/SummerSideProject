// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Enums.h"
#include "DataComponent.h"

#include "StatComponent.generated.h"

/***************************************************************************************
Title:       StatComponent
Author:      Joshua Griffis
Date:        2022/06/08
Description: The Stat component stores a table of data to add and remove stats from 
other tables, and is used to detemine Stats
*****************************************************************************************/

USTRUCT(BlueprintType)
struct FStat
{

	GENERATED_USTRUCT_BODY()

public:

	FStat() {}
	FStat(FString newName, int newValue = 0) : name(newName), value(newValue) {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-100", ClampMax = "999"))
		int value = 0;

};


UCLASS(BlueprintType, Blueprintable)
class PROJECT_API UStatComponent : public UDataComponent
{
	GENERATED_BODY()
	
	UStatComponent();

public:

	static const FString GetStaticType() { return "UStatComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

	void AddTable(UStatComponent& ActorTable);
	void RemoveTable(UStatComponent& ActorTable);
	TArray<FStat>& GetStatTable() { return table; }

	int GetStat(FString statName);
	void SetStat(FString statName, int amount);

protected:

	UPROPERTY(EditAnywhere, BlueprintType, Blueprintable)
		TArray<FStat> table;

};
