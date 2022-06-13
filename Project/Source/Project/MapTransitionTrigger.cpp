#include "MapTransitionTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "ProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Partymanager/PartyManager.h"
#include "GameManager.h"
#include "GameMode/ProjectGameModeBase.h"

// Sets default values
AMapTransitionTrigger::AMapTransitionTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	CollisionBox->SetBoxExtent(FVector(120, 50, 140));
	CollisionBox->SetSimulatePhysics(false);
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMapTransitionTrigger::OnOverlap);
	CollisionBox->SetupAttachment(RootComponent);
}

void AMapTransitionTrigger::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Guard clauses
	if (!OtherActor) { return; }

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "OtherActor exists");

	AProjectCharacter* player = Cast<AProjectCharacter>(OtherActor);
	if (!player) { return; }

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "OtherActor is Player");

	if (OtherComp->GetClass() != UCapsuleComponent::StaticClass()) { return; }

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "OtherComp is Capsule");

	//End of guard clauses

	//Get current map name, removing the prefix
	FString current = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(this))->GetCurrentMap();
	//Then send the data to the game instance

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, current);

	/*
	//The transition to the designated map destination
	UGameManager* GameManager = GetGameInstance<UGameManager>();
	*/

	UPartyManager* PartyManager = GetGameInstance()->GetSubsystem<UPartyManager>();
	
	PartyManager->MapTransition(current, destinationMap);
	
}
