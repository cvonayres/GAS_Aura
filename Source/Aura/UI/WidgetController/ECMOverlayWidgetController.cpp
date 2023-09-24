// Copyright Electronic CAD Monkey [ECM]


#include "ECMOverlayWidgetController.h"
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetHealthAttribute()).AddUObject(this, &UECMOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UECMOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetStaminaAttribute()).AddUObject(this, &UECMOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UECMOverlayWidgetController::MaxStaminaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetManaAttribute()).AddUObject(this, &UECMOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UECMOverlayWidgetController::MaxManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetArmorAttribute()).AddUObject(this, &UECMOverlayWidgetController::ArmorChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetMaxArmorAttribute()).AddUObject(this, &UECMOverlayWidgetController::MaxArmorChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetShieldAttribute()).AddUObject(this, &UECMOverlayWidgetController::ShieldChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ECMAttributeSet->GetMaxShieldAttribute()).AddUObject(this, &UECMOverlayWidgetController::MaxShieldChanged);
}

void UECMOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}
void UECMOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UECMOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}
void UECMOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}

void UECMOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}
void UECMOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UECMOverlayWidgetController::ArmorChanged(const FOnAttributeChangeData& Data) const
{
	OnArmorChanged.Broadcast(Data.NewValue);
}
void UECMOverlayWidgetController::MaxArmorChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxArmorChanged.Broadcast(Data.NewValue);
}

void UECMOverlayWidgetController::ShieldChanged(const FOnAttributeChangeData& Data) const
{
	OnShieldChanged.Broadcast(Data.NewValue);
}
void UECMOverlayWidgetController::MaxShieldChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxShieldChanged.Broadcast(Data.NewValue);
}
