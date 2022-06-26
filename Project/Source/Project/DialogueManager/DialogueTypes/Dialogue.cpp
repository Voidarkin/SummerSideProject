#include "Dialogue.h"
#include "../../UI/DialogueScreen.h"

void UDialogue::Display(UDialogueScreen* DialogueUI)
{
	DialogueUI->SetDialogueStyle();
	DialogueUI->SetDialogueName(DialogueName);
	DialogueUI->SetDialogueText(DialogueText);
}
