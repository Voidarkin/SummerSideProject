#include "DatabaseManager.h"
#include "ItemDatabase.h"
#include "CharacterDatabase.h"

UDatabaseManager::UDatabaseManager()
{
	ItemDatabase = Cast<UItemDatabase>(UItemDatabase::StaticClass()->GetDefaultObject());
	CharacterDatabase = Cast<UCharacterDatabase>(UCharacterDatabase::StaticClass()->GetDefaultObject());
}

