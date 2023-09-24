// Copyright Electronic CAD Monkey [ECM]

#include "ECMAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UECMAttributeSet::UECMAttributeSet()
{
	// Vital Attributes TODO Review where to set these
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitStamina(50.f);
	InitMaxStamina(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
	InitArmor(50.f);
	InitMaxArmor(100.f);
	InitShield(50.f);
	InitMaxShield(100.f);
}

// Clamp Valves
void UECMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Clamp Valves
	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if(Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if(Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxArmor());

	}
	if(Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxShield());
	}
}

// Harvest Data
void UECMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
}
void UECMAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	// Source = causer, Target = target of the effect (owner of this AS)

	//Get Context Handle
	Props.EffectContextHandle = Data.EffectSpec.GetContext();

	//Get Source Ability System Component
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// Get Source Actor, Controller & Character
	if(IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor =  Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		if(Props.SourceASC->AbilityActorInfo)
		{
			Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
			if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
			{
				if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
				{
					Props.SourceController = Pawn->GetController();
				}
			}
			if(Props.SourceController)
			{
				Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
			}
		}
	}

	// Get Target Actor, Controller & Character
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetActor);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetActor);
	}
}

// Replicate attributes
void UECMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes to be replicated
	#pragma region RepVitalAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Health, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Mana, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Armor, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Shield, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);
	#pragma endregion RepVitalAttributes
	
	// Primary Attributes to be replicated
	#pragma region RepPrimaryAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Str, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Dex, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Con, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Int, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Wis, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Cha, COND_None, REPNOTIFY_Always);
	#pragma endregion RepPrimaryAttributes

	// Secondary Attributes to be replicated
	#pragma region RepSecondaryAttributes
		// Place holder for Secondary Attributes for replication to be placed
	#pragma endregion RepSecondaryAttributes
	
	// Tertiary Attributes to be replicated
	#pragma region RepTertiaryAttributes
		// Place holder for Tertiary Attributes for replication to be placed
	#pragma endregion RepTertiaryAttributes
}

// Vital - Gameplay Attributes
#pragma region VitalAttributes
	void UECMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Health, OldHealth);
}
	void UECMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, MaxHealth, OldMaxHealth);
}
	void UECMAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Stamina, OldStamina);
}
	void UECMAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, MaxStamina, OldMaxStamina);
}
	void UECMAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Mana, OldMana);
}
	void UECMAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, MaxMana, OldMaxMana);
}	
	void UECMAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Armor, OldArmor);
}
	void UECMAttributeSet::OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, MaxArmor, OldMaxArmor);
}
	void UECMAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Shield, OldShield);
}
	void UECMAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, MaxShield, OldMaxShield);
}
#pragma endregion VitalAttributes

// Primary - Gameplay Attributes
#pragma region PrimaryAttributes
	void UECMAttributeSet::OnRep_Str(const FGameplayAttributeData& OldStr) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Str, OldStr);
}
	void UECMAttributeSet::OnRep_Dex(const FGameplayAttributeData& OldDex) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Dex, OldDex);
}
	void UECMAttributeSet::OnRep_Con(const FGameplayAttributeData& OldCon) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Con, OldCon);
}
	void UECMAttributeSet::OnRep_Int(const FGameplayAttributeData& OldInt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Int, OldInt);
}
	void UECMAttributeSet::OnRep_Wis(const FGameplayAttributeData& OldWis) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Wis, OldWis);
}
	void UECMAttributeSet::OnRep_Cha(const FGameplayAttributeData& OldCha) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Cha, OldCha);
}
#pragma endregion PrimaryAttributes

// Secondary - Gameplay Attributes
#pragma region SecondaryAttributes
	// Place holder for Secondary Attributes to be placed
#pragma endregion SecondaryAttributes

// Tertiary - Gameplay Attributes
#pragma region TertiaryAttributes
	// Place holder for Tertiary Attributes to be placed
#pragma endregion TertiaryAttributes

