// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ECMCharacterBase.generated.h"

UCLASS()
class AURA_API AECMCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AECMCharacterBase();

protected:
	virtual void BeginPlay() override;
	
};
