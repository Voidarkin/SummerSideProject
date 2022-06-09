// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "DataComponent.h"

#include "ConditionTableComponent.generated.h"

/***************************************************************************************
Title:       ConditionTableComponent
Author:      Joshua Griffis
Date:        2022/06/08
Description: Stores the resistances of conditions
*****************************************************************************************/

USTRUCT(BlueprintType)
struct FConditionInfo
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-100", ClampMax = "100"))
		int32 value = 0;

};


UCLASS(BlueprintType, Blueprintable)
class PROJECT_API UConditionTableComponent : public UDataComponent
{
	GENERATED_BODY()

public:

	static const FString GetStaticType() { return "UConditionTableComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

public:
	// Sets default values for this component's properties
	UConditionTableComponent();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsResistance;

	UPROPERTY(EditAnywhere, BlueprintType, Blueprintable)
		TArray<FConditionInfo> table;

public:
	void AddTable(UConditionTableComponent& ActorTable);
	void RemoveTable(UConditionTableComponent& ActorTable);
	TArray<FConditionInfo>& GetConditionTable() { return table; }

};


