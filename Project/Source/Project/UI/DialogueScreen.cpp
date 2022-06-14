#include "DialogueScreen.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"


void UDialogueScreen::SetDialogueText(FString Text)
{

	Text_Dialogue->SetText(FText::FromString(Text));

}

void UDialogueScreen::SetDialogueName(FString Name, bool ShowName)
{
	if (!ShowName)
	{
		Border_Name->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Border_Name->SetVisibility(ESlateVisibility::Visible);
		Text_Name->SetText(FText::FromString(Name));
	}
}

bool UDialogueScreen::Initialize()
{
	bool bResult = Super::Initialize();
	if (!bResult)
	{
		return false;
	}

	//Put buttons here if needed


	return bResult;
}

