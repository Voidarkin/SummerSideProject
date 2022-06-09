#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataComponent.generated.h"

/**
 * 
 */


UCLASS()
class PROJECT_API UDataComponent : public UObject
{
	GENERATED_BODY()
	
public:

	virtual const FString GetType() { return ""; }

};
