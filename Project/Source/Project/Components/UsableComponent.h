#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "DataComponent.h"

#include "UsableComponent.generated.h"

/***************************************************************************************
Title:       UsableComponent
Author:      Joshua Griffis
Date:        2022/06/12
Description: Component to determine how to use an item
*****************************************************************************************/

UCLASS(BlueprintType)
class PROJECT_API UUsableComponent : public UDataComponent
{

	GENERATED_BODY()

public:

	static const FString GetStaticType() { return "UUsableComponent"; }
	virtual const FString GetType() override { return GetStaticType(); }

	UFUNCTION()
		EUsable GetWhereUsable() { return UsableWhere; }
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EUsable UsableWhere;

};
