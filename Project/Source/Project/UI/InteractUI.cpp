#include "InteractUI.h"
#include "Components/TextBlock.h"

void UInteractUI::SetText(FString text)
{
	Text_Interact->SetText(FText::FromString(text));
}
