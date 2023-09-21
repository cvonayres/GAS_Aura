// Copyright Electronic CAD Monkey [ECM]


#include "ECMPlayerCameraManager.h"

AECMPlayerCameraManager::AECMPlayerCameraManager()
{
}

void AECMPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetOwningPlayerController();

	if(Controller) 
	{
		ControlledPawn = Controller->GetPawn<APawn>();
	}
}

void AECMPlayerCameraManager::GetValves(FVector& Location, FRotator& Rotation) const
{
	if (UseTopDownView)
	{
		GetTDValves(Location,Rotation);
	}
	else
	{
		GetTPFValves(Location,Rotation);
	}
}

// Calculate new location and rotation valves for Blueprint Camera Update.
void AECMPlayerCameraManager::GetTPFValves(FVector& Location, FRotator& Rotation) const
{
	if (Controller)
	{
		const FRotator ControllerRotation = Controller->GetControlRotation();
		const FRotator YawRotation (0.f, ControllerRotation.Yaw, 0.f);
	
		const FVector OffsetX = TPFOffset.X * FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector OffsetY = TPFOffset.Y * FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector OffsetZ = TPFOffset.Z * FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
	
		if (ControlledPawn)
		{
			const FVector NewLocation = ControlledPawn->GetActorLocation() + OffsetX + OffsetY + OffsetZ;

			Rotation = YawRotation;
			Location = NewLocation;
		}
	}
}
void AECMPlayerCameraManager::GetTDValves(FVector& Location, FRotator& Rotation) const
{
	if (ControlledPawn)
	{
		Rotation = TDRotation;
		Location = ControlledPawn->GetActorLocation() + TDOffset;
	}
}

// Update Camera Zoom
void AECMPlayerCameraManager::UpdateZoom(float valve)
{
	if(!ZoomCurve) return ;

	const float CurveValve = ZoomCurve->GetFloatValue(valve);
	
	if (UseTopDownView)
	{
		UpdateZoomInternal(TDOffset,CurveValve);
	}
	else
	{
		UpdateZoomInternal(TPFOffset,CurveValve);
	}
}
void AECMPlayerCameraManager::UpdateZoomInternal(FVector &Offset, float Value) const
{
	const FVector OffsetRef = Offset;
	const float UpdatedOffsetX = OffsetRef.X + Value;

	Offset = FVector (FMath::Clamp(UpdatedOffsetX,ZoomMIN,ZoomMAX),OffsetRef.Y,OffsetRef.Z);
}
