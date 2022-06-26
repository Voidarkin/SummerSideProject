#include "TalkingActor.h"
#include "../PartyManager/Inventory.h"
#include "../DialogueManager/DialogueManager.h"
#include "../DialogueManager/Conversation.h"
#include "../DialogueManager/DialogueTypes/DialogueType.h"
#include "../DialogueManager/DialogueTypes/Choice.h"
#include "../DialogueManager/DialogueTypes/Dialogue.h"
#include "../DialogueManager/DialogueTypes/Descriptor.h"

ATalkingActor::ATalkingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentConversation = 0;
}

void ATalkingActor::BeginPlay()
{
	Super::BeginPlay();

	//Check progress list to see if NPC has ways to start with different dialogue;
}

void ATalkingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATalkingActor::Interact_Implementation()
{
	UGameInstance* GameInstance = GetGameInstance();

	UDialogueManager* DialogueManager = GameInstance->GetSubsystem<UDialogueManager>();
	DialogueManager->StoreConversation(Conversations);
}
