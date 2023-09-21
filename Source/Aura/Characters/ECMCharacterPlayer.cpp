// Copyright Electronic CAD Monkey [ECM]


#include "ECMCharacterPlayer.h"

#include "Aura/Player/ECMPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

AECMCharacterPlayer::AECMCharacterPlayer()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
}

void AECMCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	ControllerRef = Cast<AECMPlayerController>(GetController());

	UpdatedViewMode();

}

void AECMCharacterPlayer::UpdatedViewMode()
{
	if(!ControllerRef) return;

	if(ControllerRef->ViewMode == EViewMode::FPV)
	{
		
	}
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
