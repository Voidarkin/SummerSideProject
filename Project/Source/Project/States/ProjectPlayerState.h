#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../Enums.h"
#include "ProjectPlayerState.generated.h"

/***************************************************************************************
Title:       ProjectPlayerState
Author:      Joshua Griffis
Date:        2022/06/26
Description: The players states and certain variables are stored here
*****************************************************************************************/

UCLASS()
class PROJECT_API AProjectPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	void ChangeState(EState state);
	EState GetCurrentState() { return State; }

protected:

	EState State = EState::Default;

};
