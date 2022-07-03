#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "DataComponent.h"

#include "ConditionComponent.generated.h"

/***************************************************************************************
Title:       ConditionComponent
Author:      Joshua Griffis
Date:        2022/06/08
Description: Data to determine healing or inflicting a condition and its success chance.
*****************************************************************************************/

UCLASS()
class PROJECT_API UConditionComponent : public UDataComponent
{
	GENERATED_BODY()

public:

	static const FString GetStaticType() { return "UConditionComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEffect Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EConditionTypes Conditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SuccessChance;
};

