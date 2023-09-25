// Copyright Electronic CAD Monkey [ECM]


#include "ECMCharacterAI.h"

#include "Aura/AbilitySystem/ECMAbilitySystemComponent.h"
#include "Aura/AbilitySystem/ECMAttributeSet.h"

AECMCharacterAI::AECMCharacterAI()
{
	AbilitySystemComponent = CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AECMCharacterAI::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AECMCharacterAI::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
