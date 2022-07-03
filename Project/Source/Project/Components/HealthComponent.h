// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "DataComponent.h"

#include "HealthComponent.generated.h"

/***************************************************************************************
Title:       HealthComponent
Author:      Joshua Griffis
Date:        2022/06/08
Description: The Health component stores data needed to determine the change in health
in skills or items.
*****************************************************************************************/

UCLASS()
class PROJECT_API UHealthComponent : public UDataComponent
{
	GENERATED_BODY()
		
public:

	static const FString GetStaticType() { return "UHealthComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

public:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEffect Effect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Value;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	DamageType;	
public:

	UFUNCTION()
		EEffect GetEffect() { return Effect; }
	UFUNCTION()
		uint16 GetValue() { return Value; }

};
