// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Aura/Interaction/ECMHightlightInterface.h"
#include "GameFramework/Character.h"
#include "ECMCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AECMCharacterBase : public ACharacter, public IECMHightlightInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AECMCharacterBase();
	
	/* Hightlight Interface */
	virtual void HighlightActor() override;
	virtual void UnHightlighActor() override;
	/* end Hightlight Interface */

	// Getters for Attribute System
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	// Points for Attribute System
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// Optional BP function called on highlighed
	UFUNCTION(BlueprintImplementableEvent)
	void Highlighted(bool State);

	virtual void InitAbilityActorInfo();

private:
	
};
