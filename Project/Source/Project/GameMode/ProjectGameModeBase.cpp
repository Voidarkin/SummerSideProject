// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"
#include "../PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
//#include "PDPlayerState.h"


AProjectGameModeBase::AProjectGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	static ConstructorHelpers::FClassFinder<AMyPlayerController> PlayerController(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_MyPlayerController"));

	//static ConstructorHelpers::FClassFinder<APlayerState> PlayerState(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_PDPlayerState"));

	if (PawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PawnBPClass.Class;
	}
	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}
	//if (PlayerState.Class != NULL)
	//{
	//	PlayerStateClass = PlayerState.Class;
	//}
}

void AProjectGameModeBase::BeginPlay()
{
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->EnableLoadingScreen();
}