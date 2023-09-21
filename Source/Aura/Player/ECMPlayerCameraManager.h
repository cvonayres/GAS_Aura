// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

UCLASS()
class AURA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AECMPlayerCameraManager();

	// Zoom public function
	void UpdateZoom(float valve);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	void GetValves(FVector &Location, FRotator &Rotation) const;

	// View Settings
	UPROPERTY(EditAnywhere, Category="Camera Settings")
	bool UseTopDownView;
	UPROPERTY(EditAnywhere, Category="Camera Settings")
	FVector TPFOffset;
	UPROPERTY(EditAnywhere, Category="Camera Settings")
	FVector TDOffset;
	UPROPERTY(EditAnywhere, Category="Camera Settings")
	FRotator TDRotation;
	
	// Zoom Controls
	UPROPERTY(EditAnywhere, Category="Camera Settings|Zoom")
	UCurveFloat* ZoomCurve;
	UPROPERTY(EditAnywhere, Category="Camera Settings|Zoom")
	float ZoomMAX;
	UPROPERTY(EditAnywhere, Category="Camera Settings|Zoom")
	float ZoomMIN;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Referances")
	APlayerController* Controller;
	UPROPERTY(VisibleAnywhere, Category="Referances")
	APawn* ControlledPawn;

	void GetTPFValves(FVector &Location, FRotator &Rotation) const;
	void GetTDValves(FVector &Location, FRotator &Rotation) const;
	void UpdateZoomInternal(FVector &Offset, float Value) const;
};

