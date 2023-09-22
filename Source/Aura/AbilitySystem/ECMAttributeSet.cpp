// Copyright Electronic CAD Monkey [ECM]

#include "ECMAttributeSet.h"
#include "Net/UnrealNetwork.h"

UECMAttributeSet::UECMAttributeSet()
{
	// Vital Attributes TODO Review where to set these
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitSprint(100.f);
	InitMaxSprint(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
	InitArmor(0.f);
	InitMaxArmor(0.f);
	InitShield(0.f);
	InitMaxShield(0.f);
}

// Replicate attributes
void UECMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes to be replicated
	#pragma region RepVitalAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Health, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Sprint, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, MaxSprint, COND_None, REPNOTIFY_Always);
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
	void UECMAttributeSet::OnRep_Sprint(const FGameplayAttributeData& OldSprint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, Sprint, OldSprint);
}
	void UECMAttributeSet::OnRep_MaxSprint(const FGameplayAttributeData& OldMaxSprint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UECMAttributeSet, MaxSprint, OldMaxSprint);
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
