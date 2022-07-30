// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../MapTransitionTrigger.h"
#include "../ProjectCharacter.h"
#include "../UI/LoadingScreen.h"
#include "../UI/InventoryUI.h"
#include "../PlayerController/MyPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "../GameManager.h"
#include "Engine/World.h"
#include "Inventory.h"
#include "../Data/CharacterData.h"
#include "../Data/DatabaseManager.h"
#include "../Data/CharacterDatabase.h"
#include "../GameMode/ProjectGameModeBase.h"
#include "../Interactables/Chest.h"


UPartyManager::UPartyManager()
{

	Inventory = Cast<UInventory>(UInventory::StaticClass()->GetDefaultObject());

	//Starting Party Members
	//AddPartyMember("");

	//Starting Recipes
	KnownRecipes.Add("Potion");

	static ConstructorHelpers::FClassFinder<UInventoryUI> InventoryUI_BP_Class(TEXT("/Game/ThirdPersonCPP/Blueprints/UI/WBP_Inventory"));
	if (InventoryUI_BP_Class.Class != NULL)
	{
		InventoryUI_BP = InventoryUI_BP_Class.Class;
		UGameInstance* GameInstance = GetGameInstance();
		if (GameInstance)
		{
			InventoryUI = CreateWidget<UInventoryUI>(GameInstance, InventoryUI_BP);
		}

	}

}

void UPartyManager::ToggleInventory()
{
	InventoryUI->SetInventorySlots();
	if (InventoryUI->IsInViewport())
	{
		InventoryUI->RemoveFromViewport();
		Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputModeUI(EGameInputMode::GameOnly);
	}
	else
	{
		InventoryUI->AddToViewport();
		Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputModeUI(EGameInputMode::GameAndUI);
	}
}

void UPartyManager::MapTransition(FString currentMap, FString nextMap)
{
	
	//Transition to new level
	UGameplayStatics::OpenLevel(GetWorld(), FName(nextMap));
	currentMapName = nextMap;
	previousMapName = currentMap;
	EnableLoadingScreen();

	//TODO: Make sure it remains active after transitions
	/*
	//Setup a load screen here

	//Setup timer and then apply to next map
	GetWorld()->GetTimerManager().ClearTimer(LoadingScreenTimer);
	GetWorld()->GetTimerManager().SetTimer(LoadingScreenTimer, this, &UPartyManager::EnableLoadingScreen, 0.01f);

	GetWorld()->GetTimerManager().ClearTimer(MapTransitionTimer);
	GetWorld()->GetTimerManager().SetTimer(MapTransitionTimer, this, &UPartyManager::TeleportPlayerAfterTransition, 1.0f);
	*/

}

void UPartyManager::EnableLoadingScreen()
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->EnableLoadingScreen();
}

void UPartyManager::AddInventoryItem(FString name, int amount) { Inventory->AddItem(name, amount); }
void UPartyManager::RemoveInventoryItem(FString name, int amount) { Inventory->RemoveItem(name, amount); }

TArray<bool> UPartyManager::GetChestListForCurrent()
{
	FString current = GetWorld()->GetGameInstance<UGameManager>()->GetCurrentMap();
	return GetChestListFor(current);
}

void UPartyManager::AddChestToList(int chestNum)
{
	FString current = GetWorld()->GetGameInstance<UGameManager>()->GetCurrentMap();
	OpenedChests[current][chestNum] = true;
}

bool UPartyManager::IsChestInList(int chestNum)
{
	FString current = GetWorld()->GetGameInstance<UGameManager>()->GetCurrentMap();
	//If the chest list for the map hasnt been created yet, create it here and populate it with default values
	if (!OpenedChests.Contains(current))
	{
		OpenedChests.Add(current);
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChest::StaticClass(), FoundActors);
		for (int i = 0; i < FoundActors.Num(); i++)
		{
			OpenedChests[current].Add(false);
		}
	}
	return OpenedChests[current][chestNum];
}

UCharacterData* UPartyManager::GetPartyMember(FString name)
{
	for (UCharacterData* character : PartyMembers)
	{
		if (character->GetCharacterName() == name)
		{
			return character;
		}
	}
	return nullptr;
}

void UPartyManager::AddPartyMember(FString characterName)
{
	UCharacterData* character = GetGameInstance()->GetSubsystem<UDatabaseManager>()->GetCharacterDatabase()->GetCharacter(characterName);
	if (character)
	{
		AddPartyMember(character);
	}
}

void UPartyManager::AddPartyMember(UCharacterData* character)
{
	CurrentPartyMembers.Add(character);
	CurrentPartySize++;
}

void UPartyManager::RemovePartyMember(FString characterName)
{
	UCharacterData* character = GetGameInstance()->GetSubsystem<UDatabaseManager>()->GetCharacterDatabase()->GetCharacter(characterName);
	if (character)
	{
		RemovePartyMember(character);
	}
}

void UPartyManager::RemovePartyMember(UCharacterData* character)
{
	CurrentPartyMembers.RemoveSingle(character);
	CurrentPartySize--;
}
