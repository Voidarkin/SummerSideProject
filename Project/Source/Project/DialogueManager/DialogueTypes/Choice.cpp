#include "Choice.h"
#include "../../UI/DialogueScreen.h"
#include "Components/VerticalBox.h"

void UChoice::Display(UDialogueScreen* DialogueUI)
{
	DialogueUI->SetChoiceStyle();

	UVerticalBox* ChoiceList = DialogueUI->GetChoiceList();
	if (!ChoiceList) { return; }


	//Add choices to ChoiceList
	//Set each button to the values for each choice.

}
