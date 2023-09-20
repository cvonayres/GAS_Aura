// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ECMPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class AURA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AECMPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Referances")
	class AECMPlayerCameraManager* CameraManager;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ZoomAction;

	void Move(const FInputActionValue& InputActionValve);
	void ZoomCamera(const FInputActionValue& InputActionValve);

};
