// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interactable.h"

#include "Chest.generated.h"

/***************************************************************************************
Title:       Chest
Author:      Joshua Griffis
Date:        2022/06/13
Description: An interactable to store an item into the inventory
*****************************************************************************************/

class UInventory;
class UDescriptor;

UCLASS()
class PROJECT_API AChest : public AInteractableBase
{
	GENERATED_BODY()
	
public:	
	AChest();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ID")
		uint8 ChestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* ClosedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* OpenedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadWrite)
		UDescriptor* ChestDialogue;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FString ItemName;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		uint8 ItemAmount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bOpened;

protected:
	virtual void BeginPlay() override;

public:	

	void CheckIfOpened();
	virtual bool CanBeInteractedWith() override;

	virtual void Interact_Implementation() override;

};
