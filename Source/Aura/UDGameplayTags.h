#pragma once

#include "NativeGameplayTags.h"

/** Declares the "Vital Attributes" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Health_Current)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Health_Max)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Stamina_Current)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Stamina_Max)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Mana_Current)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Mana_Max)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Armor_Current)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Armor_Max)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Shield_Current)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Shield_Max)

/** Declares the "Primary Attributes" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Str)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Dex)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Con)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Int)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Wis)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Cha)

/** Declares the "Secondary Attributes" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_Test)

/** Declares the "Tertiary Attributes" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Tertiary_Test)

/** Declares the "Attribute Modification Type" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Modifer_Heal)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Modifer_Damage)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Modifer_HOT)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Modifer_DOT)

/** Declares the "Attribute Modification Type" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message_HealthPotion)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message_ManaPotion)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message_HealthCrystal)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message_ManaCrystal)


//const FString Msg = FString::Printf(TEXT("GE Tag: %s), Tag.GetTagName())
//GEngine->AddOnScreenDebugMessage(1,8.f, FColor::Blue, Msg);
	