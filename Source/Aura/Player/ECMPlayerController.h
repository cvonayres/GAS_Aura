// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ECMPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IECMHightlightInterface;
struct FInputActionValue;

UENUM()
enum EViewMode
{
	FPV    UMETA(DisplayName = "First Person View"),
	TPV      UMETA(DisplayName = "Third Person View"),
	TDV   UMETA(DisplayName = "Top Down View"),
  };

UCLASS()
class AURA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AECMPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera Settings")
	TEnumAsByte<EViewMode> ViewMode;

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

	void CurserTrace();
	IECMHightlightInterface* LastActor;
	IECMHightlightInterface* ThisActor;
};
