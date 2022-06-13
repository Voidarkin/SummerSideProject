#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Engine/DataAsset.h"

#include "CharacterDatabase.generated.h"

/***************************************************************************************
Title:       CharacterDatabase
Author:      Joshua Griffis
Date:        2022/06/12
Description: Stores all the characters in an array to be referenced
*****************************************************************************************/

class UCharacterData;

UCLASS()
class PROJECT_API UCharacterDatabase : public UObject
{

	GENERATED_BODY()

public:

	UCharacterDatabase();

	UCharacterData* GetCharacter(FString pName);

protected:

	TArray<UCharacterData*> Database;

	void OnRegistryLoaded();

};
