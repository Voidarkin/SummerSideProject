#pragma once

#include "CoreMinimal.h"
#include "DialogueType.h"
#include "Choice.generated.h"

/***************************************************************************************
Title:       Choice
Author:      Joshua Griffis
Date:        2022/06/20
Description: Dialogue type that has a choice involved for decisions, or splitting dialogue
*****************************************************************************************/

UCLASS()
class PROJECT_API UChoice : public UDialogueType
{
	GENERATED_BODY()
public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FString DialgoueText;

public:
	static const FString GetStaticType() { return "UChoice"; }
	virtual const FString GetType() override { return GetStaticType(); }

	virtual void Display(UDialogueScreen* DialogueUI) override;
};
