#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"



class ULoadingScreen;


UENUM(BlueprintType)
enum class EGameInputMode : uint8
{
	UIOnly = 0 UMETA(DisplayName = "UI Only"),
	GameAndUI = 1  UMETA(DisplayName = "Game And UI"),
	GameOnly = 2     UMETA(DisplayName = "Game Only"),
	Count
};

UCLASS()
class PROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController();

	UPROPERTY()
		ULoadingScreen* LoadingScreenWidget;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ULoadingScreen> LoadingScreenBP;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void AcknowledgePossession(APawn* PossesedPawn) override;

	void Jump();
	void StopJumping();
	void MoveForward(float value);
	void MoveRight(float value);
	void SpeedUp();
	void SlowDown();

	void Interact();
	void ToggleInventory();


	//void AddControllerYawInput(float Val);
	void TurnAtRate(float Rate);
	//void AddControllerPitchInput(float Val);
	void LookUpAtRate(float Rate);

	class APlayerState* MyPlayerState;
	class AProjectCharacter* MyPawn;

public:

	void EnableLoadingScreen();
	void DisableLoadingScreen();

	void SetInputModeUI(EGameInputMode InputMode);

};
