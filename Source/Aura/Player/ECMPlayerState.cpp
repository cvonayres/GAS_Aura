// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerState.h"
#include "Aura/AbilitySystem/ECMAbilitySystemComponent.h"
#include "Aura/AbilitySystem/ECMAttributeSet.h"

AECMPlayerState::AECMPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AECMPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
