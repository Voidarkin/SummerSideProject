// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapTransitionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMapTransitionTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	
	AMapTransitionTrigger();

	UPROPERTY(EditAnywhere, Category = Collision)
		class UBoxComponent* CollisionBox;

	UPROPERTY(BlueprintReadWrite, EditInstanceonly, Category = MapTransition)
		FString destinationMap;

	UPROPERTY(BlueprintReadWrite, EditInstanceonly, Category = MapTransition)
		AActor* exitLocation;

public:

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent
			, AActor* OtherActor
			, UPrimitiveComponent* OtherComp
			, int32 OtherBodyIndex
			, bool bFromSweep
			, const FHitResult& SweepResult);

};
