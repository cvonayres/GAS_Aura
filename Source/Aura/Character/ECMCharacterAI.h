// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "ECMCharacterAI.generated.h"


UCLASS()
class AURA_API AECMCharacterAI : public AECMCharacterBase
{
	GENERATED_BODY()

public:
	AECMCharacterAI();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
};
