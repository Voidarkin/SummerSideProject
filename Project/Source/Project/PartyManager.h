// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartyManager.generated.h"

/**
 * 
 */

class ULoadingScreen;

UCLASS()
class PROJECT_API UPartyManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPartyManager();

public:

	void MapTransition(FString currentMap, FString nextMap);

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
	

protected:

	void EnableLoadingScreen();
	void TeleportPlayerAfterTransition();

};
