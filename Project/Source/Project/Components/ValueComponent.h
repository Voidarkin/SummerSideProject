#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataComponent.h"

#include "ValueComponent.generated.h"

/***************************************************************************************
Title:       ValueComponent
Author:      Joshua Griffis
Date:        2022/06/12
Description: Component to determine value
*****************************************************************************************/

UCLASS(BlueprintType)
class PROJECT_API UValueComponent : public UDataComponent
{

	GENERATED_BODY()

public:

	static const FString GetStaticType() { return "UValueComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

	UFUNCTION()
		const int GetValue() { return Value; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Value;

};
