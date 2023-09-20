// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"

AECMCharacterBase::AECMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AECMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
