// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerController.h"
#include "ECMPlayerCameraManager.h"
#include "EnhancedInputSubsystems.h"
#include  "EnhancedInputComponent.h"

AECMPlayerController::AECMPlayerController()
{
	bReplicates = true;
}

void AECMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	check(InputContext);
	UEnhancedInputLocalPlayerSubsystem*  Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(InputContext,0);

	// Setup Input Mode 
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	// Setup cursor
	bShowMouseCursor=true;
	DefaultMouseCursor = EMouseCursor::Default;

	CameraManager =  Cast<AECMPlayerCameraManager>(PlayerCameraManager);
}

// Cast InputComponent and bind Input Actions
void AECMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AECMPlayerController::Move);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerController::ZoomCamera);
}

// Move Function
void AECMPlayerController::Move(const FInputActionValue& InputActionValve)
{
	const FVector2d InputAxisVector = InputActionValve.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

// Zoom Camera
void AECMPlayerController::ZoomCamera(const FInputActionValue& InputActionValve)
{
	CameraManager->UpdateZoom(InputActionValve.Get<float>());
}
