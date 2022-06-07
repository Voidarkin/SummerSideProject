// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MapTransitionTrigger.h"
#include "ProjectCharacter.h"
#include "UI/LoadingScreen.h"
#include "PlayerController/MyPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"


UPartyManager::UPartyManager()
{
	
}

void UPartyManager::MapTransition(FString currentMap, FString nextMap)
{
	
	//Transition to new level
	UGameplayStatics::OpenLevel(GetWorld(), FName(nextMap));
	currentMapName = nextMap;
	previousMapName = currentMap;

	//TODO: Make sure it remains active after transitions

	//Setup a load screen here
	EnableLoadingScreen();

	//Setup timer and then apply to next map
	GetWorld()->GetTimerManager().ClearTimer(LoadingScreenTimer);
	GetWorld()->GetTimerManager().SetTimer(LoadingScreenTimer, this, &UPartyManager::EnableLoadingScreen, 0.01f);

	GetWorld()->GetTimerManager().ClearTimer(MapTransitionTimer);
	GetWorld()->GetTimerManager().SetTimer(MapTransitionTimer, this, &UPartyManager::TeleportPlayerAfterTransition, 1.0f);

}

void UPartyManager::EnableLoadingScreen()
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->EnableLoadingScreen();
}

void UPartyManager::TeleportPlayerAfterTransition()
{
	//Setting up teleporting to new location
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapTransitionTrigger::StaticClass(), FoundActors);
	AMapTransitionTrigger* locationBefore = nullptr;
	AActor* destinationLocation = nullptr;
	for (AActor* actor : FoundActors)
	{
		AMapTransitionTrigger* trigger = Cast<AMapTransitionTrigger>(actor);
		if (trigger)
		{
			if (trigger->destinationMap == previousMapName)
			{
				destinationLocation = trigger->exitLocation;
				locationBefore = trigger;
			}
		}
	}

	//Guard clauses
	if (!destinationLocation) { return; }
	if (!locationBefore) { return; }

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) { return; }

	AProjectCharacter* PlayerCharacter = Cast<AProjectCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) { return; }
	//End guard clauses
	
	//Location
	PlayerCharacter->SetActorLocation(destinationLocation->GetActorLocation());
	
	//Rotation
	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(locationBefore->GetActorLocation(), destinationLocation->GetActorLocation());
	newRotation.Pitch = 0;
	newRotation.Roll = 0;
	PlayerController->SetControlRotation(newRotation); //Set camera Direction
	PlayerCharacter->GetCapsuleComponent()->SetWorldRotation(newRotation); //Set Visible direction

	//take down the load screen after teleported to new map and location
	PlayerController->DisableLoadingScreen();
}
