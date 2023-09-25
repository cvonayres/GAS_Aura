// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"

#include "Aura/Aura.h"

AECMCharacterBase::AECMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);	

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AECMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AECMCharacterBase::InitAbilityActorInfo()
{
}

void AECMCharacterBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);

	// Blueprint implementable event
	Highlighted(true);
}

void AECMCharacterBase::UnHightlighActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

	// Blueprint implementable event
	Highlighted(false);
}

UAbilitySystemComponent* AECMCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
