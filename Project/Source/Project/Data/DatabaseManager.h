#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DatabaseManager.generated.h"

/***************************************************************************************
Title:       DatabaseManager
Author:      Joshua Griffis
Date:        2022/06/12
Description: The stored databases to reference
*****************************************************************************************/

class ItemDatabase;
class CharacterDatabase;

UCLASS()
class PROJECT_API UDatabaseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UDatabaseManager();

	UFUNCTION()
		UItemDatabase* GetItemDatabase() { return ItemDatabase; }
	UFUNCTION()
		UCharacterDatabase* GetCharacterDatabase() { return CharacterDatabase; }

protected:

	UItemDatabase* ItemDatabase;
	UCharacterDatabase* CharacterDatabase;

};
