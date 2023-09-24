// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMWidgetController.h"
#include "ECMOverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewxxxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, NewMaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmorChangedSignature, float, NewArmor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxArmorChangedSignature, float, NewMaxArmor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldChangedSignature, float, NewShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxShieldChangedSignature, float, NewMaxShield);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UECMOverlayWidgetController : public UECMWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnStaminaChangedSignature OnStaminaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnMaxStaminaChangedSignature OnMaxStaminaChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnArmorChangedSignature OnArmorChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnMaxArmorChangedSignature OnMaxArmorChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnShieldChangedSignature OnShieldChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnMaxShieldChangedSignature OnMaxShieldChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData &Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData &Data) const;

	void StaminaChanged(const FOnAttributeChangeData &Data) const;
	void MaxStaminaChanged(const FOnAttributeChangeData &Data) const;

	void ManaChanged(const FOnAttributeChangeData &Data) const;
	void MaxManaChanged(const FOnAttributeChangeData &Data) const;

	void ArmorChanged(const FOnAttributeChangeData &Data) const;
	void MaxArmorChanged(const FOnAttributeChangeData &Data) const;
	
	void ShieldChanged(const FOnAttributeChangeData &Data) const;
	void MaxShieldChanged(const FOnAttributeChangeData &Data) const;
};
