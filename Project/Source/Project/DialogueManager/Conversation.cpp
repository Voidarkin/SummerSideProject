#include "Conversation.h"
#include "DialogueTypes/DialogueType.h"
#include "../UI/DialogueScreen.h"

void UConversation::DisplayConversationLine(int i, UDialogueScreen* DialogueUI)
{ 
	Ar[i]->Display(DialogueUI); 
}