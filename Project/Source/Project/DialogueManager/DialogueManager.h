#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueManager.generated.h"

/***************************************************************************************
Title:       DialogueManager
Author:      Joshua Griffis
Date:        2022/06/20
Description: Controls all dialogue systems in the game
*****************************************************************************************/

class UDialogueScreen;
class UDialogueType;

USTRUCT(BlueprintType)
struct FConversation {
	GENERATED_BODY()
public:

	TArray<UDialogueType*> Ar;

	UDialogueType* operator[] (int32 i) 
	{
		return Ar[i];
	}

	void Add(UDialogueType* DialogueType) 
	{
		Ar.Add(DialogueType);
	}

	int32 Num()
	{
		return Ar.Num();
	}
};

UCLASS()
class PROJECT_API UDialogueManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UDialogueManager();

public:

	void DisplayDialogue();
	void HideDialogue();
	void StoreConversation(FConversation conversation);
	void StoreConversation(TArray<FConversation> conversation);
	void ContinueConversation();

protected:

	//Dialogue UI
	UPROPERTY()
		UDialogueScreen* DialogueUI;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UDialogueScreen> DialogueBP;

	//Current dialogue variables
	UPROPERTY()
		TArray<FConversation> StoredConversations;

	int CurrentConversation = 0;
	int CurrentConversationProgress = 0;

protected:

	void EmptyStoredConversations();

};
