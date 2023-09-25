// Copyright Electronic CAD Monkey [ECM]


#include "ECMOverlayWidgetController.h"
#include "Aura/AbilitySystem/ECMAbilitySystemComponent.h"
#include "Aura/AbilitySystem/ECMAttributeSet.h"

// Broadcast when Attribute change
void UECMOverlayWidgetController::BroadcastInitialValues()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ECMAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ECMAttributeSet->GetMaxHealth());

	OnStaminaChanged.Broadcast(ECMAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(ECMAttributeSet->GetMaxStamina());

	OnManaChanged.Broadcast(ECMAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(ECMAttributeSet->GetMaxMana());

	OnArmorChanged.Broadcast(ECMAttributeSet->GetArmor());
	OnMaxArmorChanged.Broadcast(ECMAttributeSet->GetMaxArmor());

	OnShieldChanged.Broadcast(ECMAttributeSet->GetShield());
	OnMaxShieldChanged.Broadcast(ECMAttributeSet->GetMaxShield());
}

// Bind Listeners for Attribute change
void UECMOverlayWidgetController::BindCallbacksToDependencies()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);
	
	// Bind Health & Max Health
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	// Bind Stamina & Max Stamina
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetStaminaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)
			{
				OnMaxStaminaChanged.Broadcast(Data.NewValue);
			}
		);

	// Bind Mana & Max Mana
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	// Bind Armor & Max Armor
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetArmorAttribute()).AddLambda(
[this](const FOnAttributeChangeData &Data)
	{
		OnArmorChanged.Broadcast(Data.NewValue);
	}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetMaxArmorAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)
			{
				OnMaxArmorChanged.Broadcast(Data.NewValue);
			}
		);

	// Bind Shield & Max Shield
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetShieldAttribute()).AddLambda(
[this](const FOnAttributeChangeData &Data)
	{
		OnShieldChanged.Broadcast(Data.NewValue);
	}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetMaxShieldAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)
			{
				OnMaxShieldChanged.Broadcast(Data.NewValue);
			}
		);

	// Bind Message Widget Row
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag& Tag : AssetTags)
			{
				// Only look for row from data table if tag has message
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if(Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
		);

}
