#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "../Enums.h"

#include "InteractableBase.generated.h"

class UInteractUI;

UCLASS()
class PROJECT_API AInteractableBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractableBase();

	UPROPERTY()
		UInteractUI* InteractUI;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UInteractUI> InteractUIBP;

	UPROPERTY()
		bool bCanBeInteractedWith = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EInteractType Type = EInteractType::Interact;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual bool CanBeInteractedWith() { return bCanBeInteractedWith; }
	EInteractType GetInteractType() { return Type; }

	virtual void UpdateUILocation();
	virtual void TurnOnUI();
	virtual void TurnOffUI();
};
