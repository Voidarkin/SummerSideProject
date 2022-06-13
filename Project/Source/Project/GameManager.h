#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

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

protected:

	void TeleportPlayerAfterTransition();

};
