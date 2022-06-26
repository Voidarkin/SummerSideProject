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

USTRUCT(BlueprintType)
struct FChoiceValues
{
	GENERATED_USTRUCT_BODY()

public:

	//The choice and which conversation it continues into
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString Text = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ConversationAfterChoice = 0;

	//The choice may have story significance or quest significance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString ProgressName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ProgressValue = 0;

};

UCLASS()
class PROJECT_API UChoice : public UDialogueType
{
	GENERATED_BODY()
public:

	TArray<FChoiceValues> Choices;

public:
	static const FString GetStaticType() { return "UChoice"; }
	virtual const FString GetType() override { return GetStaticType(); }

	virtual void Display(UDialogueScreen* DialogueUI) override;
};
