// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingScreen.generated.h"

/**
 * 
 */

class UImage;
class UProgressBar;

UCLASS()
class PROJECT_API ULoadingScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
		UImage* Image_Background;

public:

	UFUNCTION()
		void Activate();
	UFUNCTION()
		void Deactivate();
};
