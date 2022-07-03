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

UCLASS(EditInlineNew, BlueprintType, Blueprintable)
class PROJECT_API UConversation : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, Instanced, BlueprintReadWrite, Category = "Conversation")
		TArray<UDialogueType*> Ar;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Conversation")
		uint8 NextConversation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Conversation")
		bool bNextConversationStarts = false;

	UDialogueType* operator[] (int32 i) { return Ar[i]; }
	void Add(UDialogueType* DialogueType) { Ar.Add(DialogueType); }
	uint16 Num() { return Ar.Num(); }
	UDialogueType* GetConversationLine(uint8 i) { return Ar[i]; }
	void DisplayConversationLine(uint8 i, UDialogueScreen* DialogueUI);

};
