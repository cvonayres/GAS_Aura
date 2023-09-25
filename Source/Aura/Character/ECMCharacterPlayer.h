// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "ECMCharacterPlayer.generated.h"

UCLASS()
class AURA_API AECMCharacterPlayer : public AECMCharacterBase
{
	GENERATED_BODY()

public:
	AECMCharacterPlayer();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY()
	class AECMPlayerController* ControllerRef;

	// Called from Player Controller
	void UpdatedViewMode();

};
