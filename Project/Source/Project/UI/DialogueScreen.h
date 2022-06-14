#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DialogueScreen.generated.h"

/***************************************************************************************
Title:       DialogueScreen
Author:      Joshua Griffis
Date:        2022/06/14
Description: Displays Dialogue
*****************************************************************************************/

class UBorder;
class UTextBlock;

UCLASS()
class PROJECT_API UDialogueScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Borders
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Name;
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Dialogue;

	//TextBlocks
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Name;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Dialogue;

public:

	//SetDialogueText: Updates dialogue UI with dialogue text
	void SetDialogueText(FString Text);
	//SetDialogueName: Updates dialogue UI with name
	void SetDialogueName(FString Name = "", bool ShowName = false);

protected:

	virtual bool Initialize() override;

};
