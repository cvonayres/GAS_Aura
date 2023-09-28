// Copyright Electronic CAD Monkey [ECM]

#include "ECMAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

struct AttributeFunctionMappings
{
	FGameplayAttribute Attribute;
	float (UECMAttributeSet::*Getter)() const = nullptr;
	void (UECMAttributeSet::*Setter)(float) = nullptr;
	float (UECMAttributeSet::*MaxFunc)() const;
};

#pragma region Clamping
// Define Vital Attributes for Clamping
TArray<AttributeFunctionMappings> UECMAttributeSet::GetVitalValvesMappings()
{
	return {
		        { GetVitalityMatrixAttribute(), &UECMAttributeSet::GetVitalityMatrix, &UECMAttributeSet::SetVitalityMatrix, &UECMAttributeSet::GetVMCapacity },
				{ GetEnergeticEnduranceAttribute(), &UECMAttributeSet::GetEnergeticEndurance, &UECMAttributeSet::SetEnergeticEndurance, &UECMAttributeSet::GetEECapacity },
				{ GetArcaneReservoirAttribute(), &UECMAttributeSet::GetArcaneReservoir, &UECMAttributeSet::SetArcaneReservoir, &UECMAttributeSet::GetARCapacity },
				{ GetDefensiveSynchronyAttribute(), &UECMAttributeSet::GetDefensiveSynchrony, &UECMAttributeSet::SetDefensiveSynchrony, &UECMAttributeSet::GetKineticAbsorption },
				{ GetBarrierMatrixAttribute(), &UECMAttributeSet::GetBarrierMatrix, &UECMAttributeSet::SetBarrierMatrix, &UECMAttributeSet::GetNanoshieldThreshold }
	};
}

// Define Primary Attributes for Clamping
TArray<AttributeFunctionMappings> UECMAttributeSet::GetPrimaryValvesMappings()
{
	return {
		        { GetPhysiqueAttribute(), &UECMAttributeSet::GetPhysique, &UECMAttributeSet::SetPhysique },
				{ GetAdaptivityAttribute(), &UECMAttributeSet::GetAdaptivity, &UECMAttributeSet::SetAdaptivity },
				{ GetNeuralAgilityAttribute(), &UECMAttributeSet::GetNeuralAgility, &UECMAttributeSet::SetNeuralAgility },
				{ GetEmpathicResonanceAttribute(), &UECMAttributeSet::GetEmpathicResonance, &UECMAttributeSet::SetEmpathicResonance },
				{ GetEssenceControlAttribute(), &UECMAttributeSet::GetEssenceControl, &UECMAttributeSet::SetEssenceControl },
				{ GetNanomancyAttribute(), &UECMAttributeSet::GetNanomancy, &UECMAttributeSet::SetNanomancy },
			};
}

// Clamp Valves
void UECMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Gets Vital Attribute Mapping and clamps valve
	const TArray<AttributeFunctionMappings> VitalValves = GetVitalValvesMappings();
	for (const auto& Mapping : VitalValves)
	{
		if (Attribute == Mapping.Attribute)
		{
			NewValue = FMath::Clamp(NewValue, 0.f, (this->*Mapping.MaxFunc)());
			return;
		}
	}

	// Gets Primary Attribute Mapping and clamps valve
	const TArray<AttributeFunctionMappings> PrimaryValves = GetPrimaryValvesMappings();
	for (const auto& Mapping : PrimaryValves)
	{
		if (Attribute == Mapping.Attribute)
		{
			NewValue = FMath::Clamp(NewValue, 0.f, MaxPrimaryAttribute);
			return;
		}
	}
}

// Harvest Data & Clamp again
void UECMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Gets GameplayEffect Prop from Data packet
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	// Gets Attribute from the Data packet
	const FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;

	// Gets Vital Attribute Mapping and clamps valve
	const TArray<AttributeFunctionMappings> VitalValves = GetVitalValvesMappings();
	for (const auto& Mapping : VitalValves)
	{
		if (Attribute == Mapping.Attribute)
		{
			float currentValue = (this->*Mapping.Getter)();
			float maxVal = (this->*Mapping.MaxFunc)();
			(this->*Mapping.Setter)(FMath::Clamp(currentValue, 0.f, maxVal));
			return;
		}
	}

	// Gets Primary Attribute Mapping and clamps valve
	const TArray<AttributeFunctionMappings> PrimaryValves = GetPrimaryValvesMappings();
	for (const auto& Mapping : PrimaryValves)
	{
		if (Attribute == Mapping.Attribute)
		{
			float currentValue = (this->*Mapping.Getter)();
			(this->*Mapping.Setter)(FMath::Clamp(currentValue, 0.f, MaxPrimaryAttribute));
			return;
		}
	}
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
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, VitalityMatrix, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EnergeticEndurance, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ArcaneReservoir, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, DefensiveSynchrony, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, BarrierMatrix, COND_None, REPNOTIFY_Always);
	#pragma endregion RepVitalAttributes
	
	// Primary Attributes to be replicated
	#pragma region RepPrimaryAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Physique, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Adaptivity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, NeuralAgility, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EmpathicResonance, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EssenceControl, COND_None, REPNOTIFY_Always);
	#pragma endregion RepPrimaryAttributes

	// Secondary Attributes to be replicated
	#pragma region RepSecondaryAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, VMCapacity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, VMRecovery, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EECapacity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EERecovery, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ARCapacity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ARRecovery, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, KineticAbsorption, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, NanoshieldThreshold, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ResonanceSyncQuality, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ResonanceAmplification, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EmpathicInfluence, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, TechnologicalInterface, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, SignalStealth, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ReactionSpeed, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, DimensionalPocketCapacity, COND_None, REPNOTIFY_Always);
	#pragma endregion RepSecondaryAttributes
	
	// Tertiary Attributes to be replicated
	#pragma region RepTertiaryAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Level, COND_None, REPNOTIFY_Always);
	#pragma endregion RepTertiaryAttributes
}
#pragma endregion Clamping

#pragma region RefNofifies
// Macro for creating  repetitive Repfunctions
#define DEFINE_ATTRIBUTE_REPNOTIFY(ClassName, AttributeName) \
void ClassName::OnRep_##AttributeName(const FGameplayAttributeData& Old##AttributeName) const \
{ \
GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, AttributeName, Old##AttributeName); \
}

// Vital - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, VitalityMatrix)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EnergeticEndurance)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ArcaneReservoir)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, DefensiveSynchrony)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, BarrierMatrix)

// Primary - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Physique)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Adaptivity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, NeuralAgility)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EmpathicResonance)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EssenceControl)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Nanomancy)

// Secondary - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, VMCapacity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, VMRecovery)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EECapacity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EERecovery)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ARCapacity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ARRecovery)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, KineticAbsorption)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, NanoshieldThreshold)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ResonanceSyncQuality)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ResonanceAmplification)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EmpathicInfluence)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, TechnologicalInterface)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, SignalStealth)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ReactionSpeed)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, DimensionalPocketCapacity)

// Tertiary - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Level)

// Undefine the macro to prevent possible interference with other code
#undef DEFINE_ATTRIBUTE_REPNOTIFY

#pragma endregion RefNofifies
