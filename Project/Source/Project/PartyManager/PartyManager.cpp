// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../MapTransitionTrigger.h"
#include "../ProjectCharacter.h"
#include "../UI/LoadingScreen.h"
#include "../PlayerController/MyPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Inventory.h"
#include "../Data/CharacterData.h"
#include "../Data/DatabaseManager.h"
#include "../Data/CharacterDatabase.h"
#include "../GameMode/ProjectGameModeBase.h"


UPartyManager::UPartyManager()
{

	Inventory = Cast<UInventory>(UInventory::StaticClass()->GetDefaultObject());

	//Starting Party Members
	//AddPartyMember("");

	//Starting Recipes
	KnownRecipes.Add("Potion");

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
	FString current = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(this))->GetCurrentMap();
	return GetChestListFor(current);
}

void UPartyManager::AddChestToList(int chestNum)
{
	FString current = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(this))->GetCurrentMap();
	OpenedChests[current][chestNum] = true;
}

bool UPartyManager::IsChestInList(int chestNum)
{
	FString current = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(this))->GetCurrentMap();
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
