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
class UVerticalBox;

UCLASS()
class PROJECT_API UDialogueScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:


	
public:

	//SetDialogueText: Updates dialogue UI with dialogue text
	void SetDialogueText(FString Text);
	//SetDialogueName: Updates dialogue UI with name
	void SetDialogueName(FString Name);

	//Makes certain widgets visible
	void SetDescriptorStyle();
	void SetDialogueStyle();
	void SetChoiceStyle();

	UVerticalBox* GetChoiceList();

protected:

	//Borders
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Name;
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Dialogue;
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_Choice;

	//VerticalBoxes
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VerticalBox_Choices;

	//TextBlocks
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Name;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Dialogue;

protected:

	virtual bool Initialize() override;

	//Makes all widgets invisible before setting each type of
	void SetDefaultStyle();
};
