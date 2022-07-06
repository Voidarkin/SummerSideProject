#include "DialogueManager.h"
#include "Conversation.h"
#include "../UI/DialogueScreen.h"
#include "DialogueTypes/DialogueType.h"
#include "DialogueTypes/Choice.h"
#include "DialogueTypes/Dialogue.h"
#include "DialogueTypes/Descriptor.h"
#include "../States/ProjectPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerController/MyPlayerController.h"
#include "../Interactables/TalkingActor.h"

UDialogueManager::UDialogueManager()
{

	//Assigning the Dialogue Screen UI to a variable
	static ConstructorHelpers::FClassFinder<UDialogueScreen> DialogueScreenBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/UI/WBP_DialogueScreen"));
	if (DialogueScreenBPClass.Class != NULL)
	{
		DialogueBP = DialogueScreenBPClass.Class;
		UGameInstance* GameInstance = GetGameInstance();
		if (GameInstance)
		{
			DialogueUI = CreateWidget<UDialogueScreen>(GameInstance, DialogueBP);
		}

	}


}

void UDialogueManager::DisplayDialogue()
{
	if (DialogueUI->IsInViewport()) { return; }
	DialogueUI->AddToViewport();
}

void UDialogueManager::HideDialogue()
{
	if (!DialogueUI->IsInViewport()) { return; }
	DialogueUI->RemoveFromViewport();
}

void UDialogueManager::StoreConversation(UDialogueType* message)
{
	EmptyStoredConversations();
	message->Display(DialogueUI);
	DisplayDialogue();
	ChangePlayerState(EState::Dialogue);
}

void UDialogueManager::StoreConversation(UConversation* conversation)
{
	EmptyStoredConversations();	
	StoredConversations[0] = conversation;

	UpdateDialogue();
	ChangePlayerState(EState::Dialogue);
}

void UDialogueManager::StoreConversation(TArray<UConversation*> conversation, uint8 startingConversation)
{
	if (StoredConversations == conversation)
	{
		CurrentConversationProgress = 0;
		UpdateDialogue();
	}
	else
	{
		EmptyStoredConversations();
		for (int i = 0; i < conversation.Num(); i++)
		{
			StoredConversations.Add(conversation[i]);
		}
		CurrentConversation = startingConversation;
		UpdateDialogue();
	}
	ChangePlayerState(EState::Dialogue);
}

void UDialogueManager::UpdateDialogue()
{
	StoredConversations[CurrentConversation]->DisplayConversationLine(CurrentConversationProgress, DialogueUI);
	DisplayDialogue();
}

void UDialogueManager::ContinueConversation()
{
	CurrentConversationProgress++;
	if (StoredConversations.Num() == 0)
	{
		EndConversation();
		return;
	}
	if (CurrentConversationProgress >= StoredConversations[CurrentConversation]->Num())
	{
		if (!StoredConversations[CurrentConversation]->bNextConversationStarts)
		{
			EndConversation();
			return;
		}
		//check if current conversation was a choice and if it continues
		
		//end dialogue
		CurrentConversation = StoredConversations[CurrentConversation]->NextConversation;

		CurrentConversationProgress = 0;

	}
	else
	{
		//continue dialogue
		UpdateDialogue();

	}
}

void UDialogueManager::EndConversation()
{
	HideDialogue();
	ChangePlayerState(EState::Default);
}

void UDialogueManager::ChangePlayerState(EState state)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->GetPlayerState<AProjectPlayerState>()->ChangeState(state);
}

void UDialogueManager::EmptyStoredConversations()
{
	StoredConversations.Empty();
	CurrentConversation = 0;
	CurrentConversationProgress = 0;
}
