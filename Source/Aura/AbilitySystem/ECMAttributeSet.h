// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ECMAttributeSet.generated.h"

#pragma region Macros
// Macro for creating attribute getters, setters,etc
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#pragma endregion Macros

#pragma region Enums
// Enum for Vital Attributes
UENUM(BlueprintType)
enum class EVitalAttribute : uint8 {
	Health       UMETA(DisplayName="Health"),
	Stamina        UMETA(DisplayName="Stamina"),
	Mana        UMETA(DisplayName="Mana"),
	Armor       UMETA(DisplayName="Armor"),
	Shield        UMETA(DisplayName="Shield"),
};

// Enum for Primary Attributes
UENUM(BlueprintType)
enum class EPrimaryAttribute : uint8 {
	Str       UMETA(DisplayName="Strength"),
	Dex        UMETA(DisplayName="Dexterity"),
	Con        UMETA(DisplayName="Constitution "),
	Int       UMETA(DisplayName="Intelligence"),
	Wis        UMETA(DisplayName="Wisdom"),
	Cha        UMETA(DisplayName="Charisma"),
};

// Enum for Secondary Attributes
UENUM(BlueprintType)
enum class ESecondaryAttribute : uint8 {
	NoSecAtt       UMETA(DisplayName="No Secondary Attributes"),
};

// Enum for Tertiary Attributes
UENUM(BlueprintType)
enum class ETertiaryAttribute : uint8 {
	NoTerAtt      UMETA(DisplayName="No Tertiary Attributes"),
};
#pragma endregion Enums

#pragma region Struts
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	//  Effect Context Handle
	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;
	
	// Source Info
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	// Target Avatar Info
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};
#pragma endregion Struts

UCLASS()
class AURA_API UECMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UECMAttributeSet();

	// Replicate variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
// Vital - Gameplay Attributes
#pragma region VitalAttributes
	#pragma region Health
		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Health);

		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, MaxHealth);
	#pragma endregion Health

	#pragma region Stamina
		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Stamina);

		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, MaxStamina);
	#pragma endregion Stamina

	#pragma region Mana
		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Mana)
		FGameplayAttributeData Mana;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Mana);

		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxMana)
		FGameplayAttributeData MaxMana;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, MaxMana);
	#pragma endregion Mana

	#pragma region Armor
		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Armor)
		FGameplayAttributeData Armor;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Armor);

		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxArmor)
		FGameplayAttributeData MaxArmor;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, MaxArmor);
	#pragma endregion Armor

	#pragma region Shield
		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Shield)
		FGameplayAttributeData Shield;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Shield);

		UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxShield)
		FGameplayAttributeData MaxShield;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, MaxShield);
	#pragma endregion Shield

	#pragma region Vital_OnReps
		// Vital - OnReps
		UFUNCTION()
		void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
		UFUNCTION()
		void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
		UFUNCTION()
		void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
		UFUNCTION()
		void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
		UFUNCTION()
		void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
		UFUNCTION()
		void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
		UFUNCTION()
		void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
		UFUNCTION()
		void OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor) const;
		UFUNCTION()
		void OnRep_Shield(const FGameplayAttributeData& OldShield) const;
		UFUNCTION()
		void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const;
	#pragma endregion Vital_OnReps
#pragma endregion VitalAttributes

// Primary - Gameplay Attributes
#pragma region PrimaryAttributes
	#pragma region Stats
		UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Str)
		FGameplayAttributeData Str;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Str);

		UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Dex)
		FGameplayAttributeData Dex;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Dex);

		UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Con)
		FGameplayAttributeData Con;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Con);

		UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Int)
		FGameplayAttributeData Int;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Int);

		UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Wis)
		FGameplayAttributeData Wis;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Wis);

		UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Cha)
		FGameplayAttributeData Cha;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Cha);
	#pragma endregion Stats
	
	#pragma region Priamry_OnReps
		// Vital - OnReps
		UFUNCTION()
		void OnRep_Str(const FGameplayAttributeData& OldStr) const;
		UFUNCTION()
		void OnRep_Dex(const FGameplayAttributeData& OldDex) const;
		UFUNCTION()
		void OnRep_Con(const FGameplayAttributeData& OldCon) const;
		UFUNCTION()
		void OnRep_Int(const FGameplayAttributeData& OldInt) const;
		UFUNCTION()
		void OnRep_Wis(const FGameplayAttributeData& OldWis) const;
		UFUNCTION()
		void OnRep_Cha(const FGameplayAttributeData& OldCha) const;
	#pragma endregion Priamry_OnReps
#pragma endregion PrimaryAttributes

// Secondary - Gameplay Attributes
#pragma region SecondaryAttributes
	
#pragma endregion SecondaryAttributes

// Tertiary - Gameplay Attributes
#pragma region TertiaryyAttributes
	
#pragma endregion TertiaryAttributes

private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties &Props);
};
