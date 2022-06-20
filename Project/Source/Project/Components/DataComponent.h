#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataComponent.generated.h"

/***************************************************************************************
Title:       DataComponent
Author:      Joshua Griffis
Date:        2022/06/20
Description: Basic DataComponent class
*****************************************************************************************/

UCLASS()
class PROJECT_API UDataComponent : public UObject
{
	GENERATED_BODY()
	
public:

	virtual const FString GetType() { return ""; }

};
