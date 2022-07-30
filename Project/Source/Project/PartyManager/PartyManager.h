// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartyManager.generated.h"

/***************************************************************************************
Title:       PartyManager
Author:      Joshua Griffis
Date:        2022/06/12
Description: Used to store current characters, inventory, and other information that
is constantly monitored.
*****************************************************************************************/

class ULoadingScreen;
class UInventory;
class UCharacterData;
class UInventoryUI;

UCLASS()
class PROJECT_API UPartyManager : public UGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UPartyManager();

	//Inventory UI
	UPROPERTY()
		UInventoryUI* InventoryUI;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryUI> InventoryUI_BP;

public:

	//Inventory UI
	void ToggleInventory();

	//Map Transition
	void MapTransition(FString currentMap, FString nextMap);
	FString GetPreviousMapName() { return previousMapName; }

	//Item
	void AddInventoryItem(FString name, int amount);
	void RemoveInventoryItem(FString name, int amount);
	UInventory* GetInventory() { return Inventory; }
	
	TArray<FString> GetKnownRecipes() { return KnownRecipes; }

	TArray<bool> GetChestListFor(FString location) { return OpenedChests[location]; }
	TArray<bool> GetChestListForCurrent();
	void AddChestToList(int chestNum);
	bool IsChestInList(int chestNum);

	//Character
	TArray<UCharacterData*> GetCurrentPartyMembers() { return CurrentPartyMembers; }
	TArray<UCharacterData*> GetPartyMembers() { return PartyMembers; }
	UCharacterData* GetPartyMember(FString name);
	void AddPartyMember(FString characterName);
	void AddPartyMember(UCharacterData* character);
	void RemovePartyMember(FString characterName);
	void RemovePartyMember(UCharacterData* character);
	uint8 GetCurrentPartyNum() { return CurrentPartySize; }

protected:

	//Battle Transition Variables
	FString preBattleMap;
	FVector preBattleLocation;
	FRotator preBattleRotation;

	//Map Transition Variables
	FString currentMapName;
	FString previousMapName;
	//FTimerHandle LoadingScreenTimer;
	
	//Item Variables
	UInventory* Inventory;

	//Character Variables
	UPROPERTY()
		TArray<UCharacterData*> CurrentPartyMembers;
	UPROPERTY()
		TArray<UCharacterData*> PartyMembers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "3"))
		uint8 CurrentPartySize;

	//Codex
	//Turn Codex into a class to make it have its own functionality
	TArray<FString> KnownRecipes;
	TMap<FString, TArray<bool>> OpenedChests; //name of location and then id number based on chests in that location
	TMap<FString, uint8> ConversationTracker; //Keeps track of conversations for each NPC
	TMap<FString, uint8> ProgressTracker; //Story and Quest Progress Tracker
	TMap<FString, TArray<uint8>> Codex; //Uses ID numbers to keep the list organized

protected:

	void EnableLoadingScreen();

};
