#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interactable.h"

#include "TalkingActor.generated.h"

/***************************************************************************************
Title:       TalkingActor
Author:      Joshua Griffis
Date:        2022/06/26
Description: An interactable to talk to
*****************************************************************************************/

class UConversation;

UCLASS()
class PROJECT_API ATalkingActor : public AInteractableBase
{
	GENERATED_BODY()
	
public:	
	
	ATalkingActor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditInstanceOnly, Category = "Conversation")
		FString ProgressName;
	UPROPERTY(EditInstanceOnly, Instanced, BlueprintReadWrite, Category = "Conversation")
		TArray<UConversation*> Conversations;
	UPROPERTY(EditInstanceOnly, Category = "Conversation")
		uint8 CurrentConversation;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

};
