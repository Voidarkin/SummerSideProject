#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
class PROJECT_API ATalkingActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	
	ATalkingActor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditInstanceOnly, Instanced, Category = "Conversation")
		TArray<UConversation*> Conversations;

	UPROPERTY(EditInstanceOnly, Category = "Conversation")
		int CurrentConversation;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

};