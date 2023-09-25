// Copyright Electronic CAD Monkey [ECM]


#include "ECMCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "Aura/AbilitySystem/ECMAbilitySystemComponent.h"
#include "Aura/Player/ECMPlayerController.h"
#include "Aura/Player/ECMPlayerState.h"
#include "Aura/UI/HUD/ECMHUD.h"
#include "GameFramework/CharacterMovementComponent.h"

AECMCharacterPlayer::AECMCharacterPlayer()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
}

void AECMCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Controller Reference for the Server
	ControllerRef = Cast<AECMPlayerController>(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AECMCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Controller Reference for the Client
	ControllerRef = Cast<AECMPlayerController>(GetController());

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

void AECMCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	UpdatedViewMode();
}

void AECMCharacterPlayer::UpdatedViewMode()
{
	if(!ControllerRef) return;

	if(ControllerRef->ViewMode == EViewMode::FPV)
	{ }
	else if (ControllerRef->ViewMode == EViewMode::TPV)
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = true;
	}
	else if (ControllerRef->ViewMode == EViewMode::TDV)
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
	}
}

void AECMCharacterPlayer::InitAbilityActorInfo()
{
	AECMPlayerState* ECMPlayerState =  GetPlayerState<AECMPlayerState>();
	check(ECMPlayerState);

	// Get Ability System Component
	AbilitySystemComponent = ECMPlayerState->GetAbilitySystemComponent();

	// Set callbacks on ECM Ability System Component
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	// Sets callbacks for Native Ability System Component
	AbilitySystemComponent->InitAbilityActorInfo(ECMPlayerState, this);

	// Get Attribute Set
	AttributeSet = ECMPlayerState->GetAttributeSet();

	// Gets Player controller and cast ability system and attribute set to Overlap
	if(AECMPlayerController* ECMPlayerController = Cast<AECMPlayerController>(GetController()))
	{
		if(AECMHUD* ECMHUD = Cast<AECMHUD>(ECMPlayerController->GetHUD()))
		{
			ECMHUD->InitOverlay(ECMPlayerController, ECMPlayerState, AbilitySystemComponent ,AttributeSet);
		}
	}
}


