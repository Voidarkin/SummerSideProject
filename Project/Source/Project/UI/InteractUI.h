#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractUI.generated.h"

/***************************************************************************************
Title:       InteractUI
Author:      Joshua Griffis
Date:        2022/07/06
Description: UI for when player can interact with an Interactable object
*****************************************************************************************/

class UTextBlock;

UCLASS()
class PROJECT_API UInteractUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Interact;

public:

	void SetText(FString text);

};
