#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../Enums.h"
#include "DialogueManager.generated.h"

/***************************************************************************************
Title:       DialogueManager
Author:      Joshua Griffis
Date:        2022/06/20
Description: Controls all dialogue systems in the game
*****************************************************************************************/

class UDialogueScreen;
class UDialogueType;
class UConversation;
class ATalkingActor;

UCLASS()
class PROJECT_API UDialogueManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UDialogueManager();

public:

	void DisplayDialogue();
	void HideDialogue();
	void StoreConversation(UDialogueType* message);
	void StoreConversation(UConversation* conversation);
	void StoreConversation(TArray<UConversation*> conversation, uint8 startingConversation = 0);
	void UpdateDialogue();
	void ContinueConversation();
	void EndConversation();
	void ChangePlayerState(EState state);

protected:

	//Dialogue UI
	UPROPERTY()
		UDialogueScreen* DialogueUI;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UDialogueScreen> DialogueBP;

	//Current dialogue variables
	UPROPERTY()
		TArray<UConversation*> StoredConversations;

	uint8 CurrentConversation = 0;
	uint16 CurrentConversationProgress = 0;

protected:

	void EmptyStoredConversations();

};
