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
	UPROPERTY(BlueprintReadOnly, Category="Referance")
	class AECMPlayerController* ControllerRef;

protected:
	virtual void BeginPlay() override;
	
private:	
	void UpdatedViewMode();
};
