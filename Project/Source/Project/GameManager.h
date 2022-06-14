#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/***************************************************************************************
Title:       GameManager
Author:      Joshua Griffis
Date:        2022/06/14
Description: 
*****************************************************************************************/

UCLASS()
class PROJECT_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:

	FTimerHandle MapTransitionTimer;

public:

	virtual void Init() override;

	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	FString GetCurrentMap();

protected:

	void TeleportPlayerAfterTransition();

};
