#include "ProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactables/Interactable.h"
#include "DialogueManager/DialogueManager.h"
#include "States/ProjectPlayerState.h"

//////////////////////////////////////////////////////////////////////////
// AProjectCharacter

AProjectCharacter::AProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractSphere = CreateDefaultSubobject<USphereComponent>("Interact Sphere");
	InteractSphere->SetSphereRadius(200);
	InteractSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractSphere->SetSimulatePhysics(false);
	InteractSphere->SetCollisionProfileName("OverlapAll");
	InteractSphere->SetupAttachment(RootComponent);

}


void AProjectCharacter::OnResetVR()
{
	// If Project is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Project.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AProjectCharacter::Interact_Default()
{
	//Sphere Collision method getting closest interactable
	//Gather actors within interact range
	TArray<AActor*> FoundActors;
	InteractSphere->GetOverlappingActors(FoundActors, AActor::StaticClass());

	if (FoundActors.Num() == 0) { return; }

	//check if any implement Interact functions
	TArray<AActor*> interactables;
	for (auto actor : FoundActors)
	{
		if (actor->Implements<UInteractable>())
		{
			interactables.Add(actor);
		}
	}

	//find closest interactable from new list and execute


	IInteractable::Execute_Interact(interactables[0]);
	Cast<AProjectPlayerState>(GetPlayerState())->ChangeState(EState::Dialogue);
}

void AProjectCharacter::Interact_Dialogue()
{
	UDialogueManager* DialogueManager = GetGameInstance()->GetSubsystem<UDialogueManager>();
	DialogueManager->ContinueConversation();
}

void AProjectCharacter::Interact()
{
	switch (Cast<AProjectPlayerState>(GetPlayerState())->GetCurrentState())
	{
	case EState::Default:
		Interact_Default();
		break;
	case EState::Dialogue:
		Interact_Dialogue();
		break;
	case EState::Menu:
		//Interact_Menu();
		break;
	}

}

void AProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
