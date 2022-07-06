#include "Chest.h"
#include "../PartyManager/Inventory.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerController/MyPlayerController.h"
#include "../PartyManager/PartyManager.h"
#include "../DialogueManager/DialogueManager.h"
#include "../DialogueManager/Conversation.h"
#include "../DialogueManager/DialogueTypes/DialogueType.h"
#include "../DialogueManager/DialogueTypes/Descriptor.h"

AChest::AChest() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	BoxComponent->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	if (ClosedMesh)
	{
		MeshComponent->SetStaticMesh(ClosedMesh);
	}
	MeshComponent->SetupAttachment(RootComponent);

	ChestDialogue = CreateDefaultSubobject<UDescriptor>("Descriptor");

	bOpened = false;
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
	
	CheckIfOpened();

	if (!bOpened)
	{
		if (ClosedMesh)
		{
			MeshComponent->SetStaticMesh(ClosedMesh);
		}
	}
	else
	{
		if (OpenedMesh)
		{
			MeshComponent->SetStaticMesh(OpenedMesh);
		}
	}

}

void AChest::CheckIfOpened()
{
	//Check the opened chest list if this chest is in it, if it is, set it to value of true
	UGameInstance* GameInstance = GetGameInstance();
	UPartyManager* PartyManager = GameInstance->GetSubsystem<UPartyManager>();
	
	bOpened = PartyManager->IsChestInList(ChestID);
}


void AChest::Interact_Implementation()
{
	if (!bOpened)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		FString ChestText;
		if (ItemAmount > 1)
		{
			ChestText = FString::Printf(TEXT("You found %d %ss"), ItemAmount, *ItemName);
		}
		else
		{
			ChestText = FString::Printf(TEXT("You found %d %s"), ItemAmount, *ItemName);
		}

		ChestDialogue->SetDialogueText(ChestText);

		UGameInstance* GameInstance = GetGameInstance();

		UDialogueManager* DialogueManager = GameInstance->GetSubsystem<UDialogueManager>();
		DialogueManager->StoreConversation(ChestDialogue);

		// Add item to inventory below
		UPartyManager* PartyManager = GameInstance->GetSubsystem<UPartyManager>();
		PartyManager->AddInventoryItem(ItemName, ItemAmount);
		bOpened = !bOpened;

		if (OpenedMesh)
		{
			MeshComponent->SetStaticMesh(OpenedMesh);
		}

		// Add chest to opened chest list
		PartyManager->AddChestToList(ChestID);

	}
	
}

bool AChest::CanBeInteractedWith()
{
	return !bOpened;
}