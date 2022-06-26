#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Conversation.generated.h"

/***************************************************************************************
Title:       Conversation
Author:      Joshua Griffis
Date:        2022/06/26
Description: an object to store information for conversations
*****************************************************************************************/

class UDialogueType;
class UDialogueScreen;

UCLASS(BlueprintType)
class PROJECT_API UConversation : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, Instanced, BlueprintReadWrite, Category = "Conversation")
		TArray<UDialogueType*> Ar;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Conversation")
		int NextConversation;

	UDialogueType* operator[] (int32 i) { return Ar[i]; }
	void Add(UDialogueType* DialogueType) { Ar.Add(DialogueType); }
	int32 Num() { return Ar.Num(); }
	UDialogueType* GetConversationLine(int i) { return Ar[i]; }
	void DisplayConversationLine(int i, UDialogueScreen* DialogueUI);

};
