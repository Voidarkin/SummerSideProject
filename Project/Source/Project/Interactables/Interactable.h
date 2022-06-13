#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

/***************************************************************************************
Title:       Interactable
Author:      Joshua Griffis
Date:        2022/06/13
Description: Used to give interaction functionality to objects
*****************************************************************************************/

//Do Not Modify
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

//Modify
class PROJECT_API IInteractable
{

	GENERATED_BODY()

public:

	//Interact: the function called when the player uses the Interact button on an object that inherits from this interface.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Interact();

};
