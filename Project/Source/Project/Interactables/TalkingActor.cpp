#include "TalkingActor.h"
#include "../PartyManager/Inventory.h"
#include "../DialogueManager/DialogueManager.h"
#include "../DialogueManager/Conversation.h"
#include "../DialogueManager/DialogueTypes/DialogueType.h"
#include "../DialogueManager/DialogueTypes/Choice.h"
#include "../DialogueManager/DialogueTypes/Dialogue.h"
#include "../DialogueManager/DialogueTypes/Descriptor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

ATalkingActor::ATalkingActor() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OverlapComp"));
	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

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
