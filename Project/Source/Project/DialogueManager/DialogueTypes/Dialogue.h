#pragma once

#include "CoreMinimal.h"
#include "DialogueType.h"
#include "Dialogue.generated.h"

/***************************************************************************************
Title:       Dialogue
Author:      Joshua Griffis
Date:        2022/06/20
Description: Dialogue type that only has text and a name
*****************************************************************************************/

UCLASS()
class PROJECT_API UDialogue : public UDialogueType
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FString DialogueName;

public:
	static const FString GetStaticType() { return "UDialogue"; }
	virtual const FString GetType() override { return GetStaticType(); }

	virtual void Display(UDialogueScreen* DialogueUI) override;
};
