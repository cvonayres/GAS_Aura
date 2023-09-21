// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Aura/Interactions/ECMHightlightInterface.h"
#include "GameFramework/Character.h"
#include "ECMCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AECMCharacterBase : public ACharacter, public IECMHightlightInterface
{
	GENERATED_BODY()

public:
	AECMCharacterBase();
	
	//Hightlight Interface
	virtual void HighlightActor() override;
	virtual void UnHightlighActor() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UFUNCTION(BlueprintImplementableEvent)
	void Highlighted(bool State);
};
