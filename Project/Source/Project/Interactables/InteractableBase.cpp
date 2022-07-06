#include "InteractableBase.h"
#include "../UI/InteractUI.h"
#include "Kismet/GameplayStatics.h"


AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UInteractUI> InteractUIBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/UI/WBP_InteractUI"));
	if (InteractUIBPClass.Class != NULL)
	{
		InteractUIBP = InteractUIBPClass.Class;
	}
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (GameInstance)
	{
		InteractUI = CreateWidget<UInteractUI>(GameInstance, InteractUIBP);
	}
}

void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableBase::UpdateUILocation()
{
	switch (Type)
	{
	case EInteractType::Open:
		InteractUI->SetText("Open");
		break;
	case EInteractType::Talk:
		InteractUI->SetText("Talk");
		break;
	case EInteractType::Interact:
		InteractUI->SetText("Interact");
		break;
	}
	FVector WorldLocation = GetActorLocation() + FVector(0, 0, 150);
	FVector2D ScreenLocation;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);
	InteractUI->SetPositionInViewport(ScreenLocation);
}

void AInteractableBase::TurnOnUI()
{
	UpdateUILocation();
	if (InteractUI->IsInViewport()) { return; }
	InteractUI->AddToViewport();
}

void AInteractableBase::TurnOffUI()
{
	if (!InteractUI->IsInViewport()) { return; }
	InteractUI->RemoveFromViewport();
}