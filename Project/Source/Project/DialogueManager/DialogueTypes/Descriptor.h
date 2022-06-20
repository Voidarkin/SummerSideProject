#pragma once

#include "CoreMinimal.h"
#include "DialogueType.h"
#include "Descriptor.generated.h"

/***************************************************************************************
Title:       Descriptor
Author:      Joshua Griffis
Date:        2022/06/20
Description: Dialogue type that only has text
*****************************************************************************************/

UCLASS()
class PROJECT_API UDescriptor : public UDialogueType
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FString DialogueText;

public:

	static const FString GetStaticType() { return "UDescriptor"; }
	virtual const FString GetType() override { return GetStaticType(); }

	virtual void Display(UDialogueScreen* DialogueUI) override;
};
