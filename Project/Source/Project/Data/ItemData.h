// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

/***************************************************************************************
Title:       ItemData
Author:      Joshua Griffis
Date:        2022/06/12
Description: Used to store the data on Items to be used in the game
*****************************************************************************************/
/***************************************************************************************
Date:        2022/06/13
Change Log:  Added an ID number to be set in accordance with desired item list
*****************************************************************************************/

class UDataComponent;

UCLASS(Blueprintable)
class PROJECT_API UItemData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
		const int GetID() { return ID; }
	UFUNCTION()
		const FString GetItemName() { return Name; }
	UFUNCTION()
		const FString GetItemDescription() { return Description; }
	UFUNCTION()
		UTexture2D* GetSprite() { return itemSprite; }

	template <class Type>
	Type* GetComponent()
	{
		for (UDataComponent* pComponent : Components)
		{
			if (pComponent->GetType() == Type::GetStaticType())
			{
				if (pComponent)
				{
					return static_cast<Type*>(pComponent);
				}
			}
		}
		return nullptr;
	}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* itemSprite;
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Components")
		TArray<UDataComponent*> Components;

};
