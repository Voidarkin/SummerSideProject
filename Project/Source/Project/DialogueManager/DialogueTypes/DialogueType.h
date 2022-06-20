#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueType.generated.h"

/***************************************************************************************
Title:       DialogueType
Author:      Joshua Griffis
Date:        2022/06/20
Description: Basic Dialogue type class used to store an array of dialogue types to create conversations
*****************************************************************************************/

class UDialogueScreen;

UCLASS(ABSTRACT, EditInlineNew, BlueprintType, Blueprintable)
class PROJECT_API UDialogueType : public UObject
{
	GENERATED_BODY()
	
public:

	virtual const FString GetType() { return ""; }

	virtual void Display(UDialogueScreen* DialogueUI) {}

};
