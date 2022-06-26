#include "OverworldGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"
#include "../PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../States/ProjectPlayerState.h"


AOverworldGameMode::AOverworldGameMode()
{

	static ConstructorHelpers::FClassFinder<APawn> PawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/Characters/OverworldCharacter"));

	static ConstructorHelpers::FClassFinder<AMyPlayerController> PlayerController(TEXT("/Game/ThirdPersonCPP/Blueprints/Controllers/BP_MyPlayerController"));

	static ConstructorHelpers::FClassFinder<APlayerState> PlayerState(TEXT("/Game/ThirdPersonCPP/Blueprints/States/BP_PlayerState"));

	if (PawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PawnBPClass.Class;
	}
	if (PlayerController.Class != NULL)
	{
		PlayerControllerClass = PlayerController.Class;
	}
	if (PlayerState.Class != NULL)
	{
		PlayerStateClass = PlayerState.Class;
	}
}
