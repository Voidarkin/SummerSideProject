#include "DialogueManager.h"
#include "../UI/DialogueScreen.h"
#include "DialogueTypes/DialogueType.h"
#include "DialogueTypes/Choice.h"
#include "DialogueTypes/Dialogue.h"
#include "DialogueTypes/Descriptor.h"

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

void UDialogueManager::StoreConversation(FConversation conversation)
{
	EmptyStoredConversations();	
	StoredConversations[0] = conversation;
}

void UDialogueManager::StoreConversation(TArray<FConversation> conversation)
{
	EmptyStoredConversations();
	for (int i = 0; i < conversation.Num(); i++)
	{
		StoredConversations[i] = conversation[i];
	}
}

void UDialogueManager::ContinueConversation()
{

	if (CurrentConversationProgress++ != StoredConversations[CurrentConversation].Num())
	{
		//continue dialogue
		StoredConversations[CurrentConversation][CurrentConversationProgress]->Display(DialogueUI);

	}
	else
	{
		//check if current conversation was a choice and if it continues
		


		//end dialogue
		HideDialogue();
	}
}

void UDialogueManager::EmptyStoredConversations()
{
	StoredConversations.Empty();
	CurrentConversation = 0;
	CurrentConversationProgress = 0;
}
