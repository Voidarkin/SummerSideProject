// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "../ProjectCharacter.h"
//#include "PDPlayerState.h"
//#include "UI/DialogueWidget.h"
//#include "UI/MenuWidget.h"
#include "../UI/LoadingScreen.h"
#include "../DialogueManager/DialogueManager.h"
//#include "Interactables/PDInteractable.h"


AMyPlayerController::AMyPlayerController()
{

}


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (LoadingScreenBP != nullptr)
	{
		LoadingScreenWidget = CreateWidget<ULoadingScreen>(this, LoadingScreenBP);
	}
	/*
	if (DialogueWindowBP != nullptr)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(this, DialogueWindowBP);
	}

	if (MenuWindowBP != nullptr)
	{
		MenuWidget = CreateWidget<UMenuWidget>(this, MenuWindowBP);
	}
	*/
}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

}

void AMyPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{

		InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
		InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJumping);
		InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
		//InputComponent->BindAction("Speed", IE_Pressed, this, &APDPlayerController::SlowDown);
		//InputComponent->BindAction("Speed", IE_Released, this, &APDPlayerController::SpeedUp);

		InputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerController::Interact);
		//InputComponent->BindAction("Menu", IE_Pressed, this, &APDPlayerController::ToggleMenu);

		InputComponent->BindAxis("Turn", MyPawn, &AProjectCharacter::AddControllerYawInput);
		InputComponent->BindAxis("TurnRate", this, &AMyPlayerController::TurnAtRate);
		InputComponent->BindAxis("LookUp", MyPawn, &AProjectCharacter::AddControllerPitchInput);
		InputComponent->BindAxis("LookUpRate", this, &AMyPlayerController::LookUpAtRate);

	}

}

void AMyPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{
	Super::AcknowledgePossession(PossesedPawn);
	MyPawn = Cast<AProjectCharacter>(PossesedPawn);

	/*
	MyPlayerState = Cast<APDPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class %s"), TEXT("AMyPlayerController::BeginPlay: MyPlayerState Set"));
	}
*/
	if (InputComponent != nullptr)
	{
		InputComponent->BindAxis("Turn", MyPawn, &AProjectCharacter::AddControllerYawInput);
		InputComponent->BindAxis("TurnRate", this, &AMyPlayerController::TurnAtRate);
		InputComponent->BindAxis("LookUp", MyPawn, &AProjectCharacter::AddControllerPitchInput);
		InputComponent->BindAxis("LookUpRate", this, &AMyPlayerController::LookUpAtRate);
	}
}

void AMyPlayerController::Jump()
{
	if (MyPawn)
		MyPawn->Jump();
}

void AMyPlayerController::StopJumping()
{
	if (MyPawn)
		MyPawn->StopJumping();
}

void AMyPlayerController::MoveForward(float value)
{
	if (MyPawn)
		MyPawn->MoveForward(value);
}

void AMyPlayerController::MoveRight(float value)
{
	if (MyPawn)
		MyPawn->MoveRight(value);
}

void AMyPlayerController::SpeedUp()
{

}

void AMyPlayerController::SlowDown()
{

}

void AMyPlayerController::TurnAtRate(float Rate)
{
	if (MyPawn)
		MyPawn->TurnAtRate(Rate);
}

void AMyPlayerController::LookUpAtRate(float Rate)
{
	if (MyPawn)
		MyPawn->LookUpAtRate(Rate);
}

void AMyPlayerController::Interact()
{
	UDialogueManager* DialogueManager = GetGameInstance()->GetSubsystem<UDialogueManager>();
	if (DialogueManager)
	{
		DialogueManager->DisplayDialogue();
	}
}

void AMyPlayerController::EnableLoadingScreen()
{
	if (!LoadingScreenWidget) { return; }
	LoadingScreenWidget->AddToViewport();
}

void AMyPlayerController::DisableLoadingScreen()
{
	if (!LoadingScreenWidget) { return; }
	LoadingScreenWidget->RemoveFromViewport();
}
