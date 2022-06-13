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

UCLASS()
class PROJECT_API UPartyManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPartyManager();


public:

	//Map Transition
	void MapTransition(FString currentMap, FString nextMap);

	//Item
	void AddInventoryItem(FString name, int amount) { Inventory->AddItem(name, amount); }
	void RemoveInventoryItem(FString name, int amount) { Inventory->RemoveItem(name, amount); }
	UInventory* GetInventory() { return Inventory; }
	
	TArray<FString> GetKnownRecipes() { return KnownRecipes; }

	//Character
	TArray<UCharacterData*> GetCurrentPartyMembers() { return CurrentPartyMembers; }
	TArray<UCharacterData*> GetPartyMembers() { return PartyMembers; }
	UCharacterData* GetPartyMember(FString name);
	void AddPartyMember(UCharacterData* character);
	void RemovePartyMember(UCharacterData* character);
	int GetCurrentPartyNum() { return CurrentPartySize; }

protected:

	//Battle Transition Variables
	FString preBattleMap;
	FVector preBattleLocation;
	FRotator preBattleRotation;

	//Map Transition Variables
	FString currentMapName;
	FString previousMapName;
	FTimerHandle MapTransitionTimer;
	FTimerHandle LoadingScreenTimer;
	
	//Item Variables
	UInventory* Inventory;
	TArray<FString> KnownRecipes;

	//Character Variables
	UPROPERTY()
		TArray<UCharacterData*> CurrentPartyMembers;
	UPROPERTY()
		TArray<UCharacterData*> PartyMembers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "4"))
		int CurrentPartySize;

protected:

	void EnableLoadingScreen();
	void TeleportPlayerAfterTransition();

};
