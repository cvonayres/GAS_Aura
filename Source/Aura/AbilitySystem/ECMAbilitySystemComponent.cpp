// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemComponent.h"

void UECMAbilitySystemComponent::AbilityActorInfoSet()
{
	// Bind Effect Applied to callback on ASC Effect Applied To Self.
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UECMAbilitySystemComponent::EffectApplied);
}

// Braodcast on EffectApplied
void UECMAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                               FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
