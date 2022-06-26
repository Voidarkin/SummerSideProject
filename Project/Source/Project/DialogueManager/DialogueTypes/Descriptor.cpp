#include "Descriptor.h"
#include "../../UI/DialogueScreen.h"

void UDescriptor::Display(UDialogueScreen* DialogueUI)
{
	DialogueUI->SetDescriptorStyle();
	DialogueUI->SetDialogueText(DialogueText);
}
