#include "GameManager.h"
#include "PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MapTransitionTrigger.h"
#include "PartyManager/PartyManager.h"
#include "ProjectCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"


void UGameManager::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UGameManager::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGameManager::EndLoadingScreen);
}

void UGameManager::BeginLoadingScreen(const FString& InMapName)
{
	//Doesnt load UI before map is loaded
	/*
	if (!IsRunningDedicatedServer())
	{
		Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->EnableLoadingScreen();
	}
	*/
}

void UGameManager::EndLoadingScreen(UWorld* InLoadedWorld)
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->EnableLoadingScreen();
	TeleportPlayerAfterTransition();
}

void UGameManager::TeleportPlayerAfterTransition()
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
			FString previousMapName = GetSubsystem<UPartyManager>()->GetPreviousMapName();
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
	GetWorld()->GetTimerManager().ClearTimer(MapTransitionTimer);
	GetWorld()->GetTimerManager().SetTimer(MapTransitionTimer, PlayerController, &AMyPlayerController::DisableLoadingScreen, 1.0f);
}