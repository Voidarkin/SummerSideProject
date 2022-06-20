#include "DialogueScreen.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

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

void UDialogueScreen::SetDialogueText(FString Text) { Text_Dialogue->SetText(FText::FromString(Text)); }
void UDialogueScreen::SetDialogueName(FString Name) { Text_Name->SetText(FText::FromString(Name)); }

void UDialogueScreen::SetDescriptorStyle()
{
	SetDefaultStyle();
	Border_Dialogue->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueScreen::SetDialogueStyle()
{
	SetDefaultStyle();
	Border_Name->SetVisibility(ESlateVisibility::Visible);
	Border_Dialogue->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueScreen::SetChoiceStyle()
{
	SetDefaultStyle();
	Border_Choice->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueScreen::SetDefaultStyle()
{
	Border_Name->SetVisibility(ESlateVisibility::Collapsed);
	Border_Dialogue->SetVisibility(ESlateVisibility::Collapsed);
	Border_Choice->SetVisibility(ESlateVisibility::Collapsed);
}
