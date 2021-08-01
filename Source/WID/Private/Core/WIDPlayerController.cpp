// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDPlayerController.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDHUD.h"
#include "Core/WIDPlayerState.h"
#include "Core/WIDGameMode.h"
#include "Core/WIDGameUserSettings.h"
#include "Core/WIDPlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"

void AWIDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	// {{ BindAxis
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AWIDPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AWIDPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AWIDPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AWIDPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("CameraZoom"), this, &AWIDPlayerController::CameraZoom);
	// }} BindAxis

	// {{ BindAction
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AWIDPlayerController::StartJump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AWIDPlayerController::StopJump);
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AWIDPlayerController::StartRun);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AWIDPlayerController::StopRun);
	InputComponent->BindAction(TEXT("SlowWalk"), IE_Pressed, this, &AWIDPlayerController::StartSlowWalk);
	InputComponent->BindAction(TEXT("SlowWalk"), IE_Released, this, &AWIDPlayerController::StopSlowWalk);
	InputComponent->BindAction(TEXT("LookLeft"), IE_Pressed, this, &AWIDPlayerController::StartLookLeft);
	InputComponent->BindAction(TEXT("LookLeft"), IE_Released, this, &AWIDPlayerController::StopLookLeft);
	InputComponent->BindAction(TEXT("LookRight"), IE_Pressed, this, &AWIDPlayerController::StartLookRight);
	InputComponent->BindAction(TEXT("LookRight"), IE_Released, this, &AWIDPlayerController::StopLookRight);
	InputComponent->BindAction<FCameraMode>(TEXT("CameraMode0"), IE_Pressed, this, &AWIDPlayerController::ChangeCameraMode, 0);
	InputComponent->BindAction<FCameraMode>(TEXT("CameraMode1"), IE_Pressed, this, &AWIDPlayerController::ChangeCameraMode, 1);
	InputComponent->BindAction(TEXT("GameMenu"), IE_Pressed, this, &AWIDPlayerController::ToggleGameMenu);
	// }} BindAction
}

void AWIDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Reduce artifacts in level move
	if (StartBlackScreenTime > 0.0f)
	{
		AWIDPlayerCameraManager* WIDPlayerCameraManager = Cast<AWIDPlayerCameraManager>(PlayerCameraManager);
		if (IsValid(WIDPlayerCameraManager))
		{
			WIDPlayerCameraManager->StartCameraFadeWithUI(1.0f, 1.0f, StartBlackScreenTime, FLinearColor::Black, true, true);

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWIDPlayerController::StartCameraFade, StartBlackScreenTime, false);
		}
	}
	else
	{
		StartCameraFade();
	}

	// Change InputMode when moving levels
	SetSimpleInputMode(StartInputMode);

	UWIDGameUserSettings* WIDGameUserSettings = Cast<UWIDGameUserSettings>(GEngine->GetGameUserSettings());
	if (WIDGameUserSettings)
	{
		WIDGameUserSettings->ApplyGameSettings(this);
	}
}

void AWIDPlayerController::MoveForward(const float Value)
{
	if (Value == 0.0f)
		return;

	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		FRotator Rot = bUsePawnControlRotation ? GetControlRotation() : WIDCharacter->GetActorForwardVector().Rotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::X);

		WIDCharacter->AddMovementInput(Dir, Value);
	}
}

void AWIDPlayerController::MoveRight(const float Value)
{
	if (Value == 0.0f)
		return;

	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		FRotator Rot = bUsePawnControlRotation ? GetControlRotation() : WIDCharacter->GetActorForwardVector().Rotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);

		WIDCharacter->AddMovementInput(Dir, Value);
	}
}

void AWIDPlayerController::Turn(const float Value)
{
	if (Value == 0.0f)
		return;

	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->AddControllerYawInput(Value * GetWorld()->DeltaTimeSeconds);
	}
}

void AWIDPlayerController::LookUp(const float Value)
{
	if (Value == 0.0f)
		return;

	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->AddControllerPitchInput(Value * GetWorld()->DeltaTimeSeconds);
	}
}

void AWIDPlayerController::StartJump()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->StartJump();
	}
}

void AWIDPlayerController::StopJump()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->StopJumping();
	}
}

void AWIDPlayerController::StartRun()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->Run();

		AWIDHUD* WIDHUD = Cast<AWIDHUD>(GetHUD());
		if (IsValid(WIDHUD))
		{
			WIDHUD->UpdateHudEvent(EHudType::PlayerState, EHudEvent::UpdateStamina);
		}
	}
}

void AWIDPlayerController::StopRun()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->RestoreMovementState();
	}
}

void AWIDPlayerController::StartSlowWalk()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->SlowWalk();
	}
}

void AWIDPlayerController::StopSlowWalk()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->RestoreMovementState();
	}
}

void AWIDPlayerController::StartLookLeft()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->StartLookLeft();
	}
}

void AWIDPlayerController::StopLookLeft()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->StopLookLeft();
	}
}

void AWIDPlayerController::StartLookRight()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->StartLookRight();
	}
}

void AWIDPlayerController::StopLookRight()
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		WIDCharacter->StopLookRight();
	}
}

void AWIDPlayerController::ChangeCameraMode(const int32 NewMode)
{
	ECameraMode NewCameraMode = static_cast<ECameraMode>(NewMode);

	switch (NewCameraMode)
	{
	case ECameraMode::ControllerIndependent:
		bUsePawnControlRotation = true;
		break;
	case ECameraMode::ControllerDependent:
		bUsePawnControlRotation = false;
		break;
	}
}

void AWIDPlayerController::ToggleGameMenu()
{
	AWIDHUD* WIDHUD = Cast<AWIDHUD>(GetHUD());
	if (IsValid(WIDHUD))
	{
		WIDHUD->UpdateHudEvent(EHudType::GameMenu, EHudEvent::ToggleVisibility);

		if (bShowMouseCursor)
		{
			SetSimpleInputMode(EInputMode::GameOnly);
		}
		else
		{
			SetSimpleInputMode(EInputMode::UIOnly);
		}
	}
}

void AWIDPlayerController::NotifyDied()
{
	// UnPossesses to block character's movement
	UnPossess();
}

void AWIDPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// NotifyDied function is called through player state
	AWIDPlayerState* WIDPlayerState = GetPlayerState<AWIDPlayerState>();
	if (IsValid(WIDPlayerState))
	{
		WIDPlayerState->DiedDelegate.AddUObject(this, &AWIDPlayerController::NotifyDied);

		AWIDCharacter* WIDCharacter = Cast<AWIDCharacter>(aPawn);
		if (IsValid(WIDCharacter))
		{
			WIDPlayerState->DiedDelegate.AddUObject(WIDCharacter, &AWIDCharacter::NotifyDied);
		}
	}
}

void AWIDPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	AWIDPlayerState* WIDPlayerState = GetPlayerState<AWIDPlayerState>();
	if (IsValid(WIDPlayerState) && WIDPlayerState->DiedDelegate.IsBound())
	{
		WIDPlayerState->DiedDelegate.Clear();
	}
}

void AWIDPlayerController::CameraZoom(const float Value)
{
	AWIDCharacter* WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter))
	{
		USpringArmComponent* CameraBoom = WIDCharacter->GetCameraBoom();
		if (CameraBoom)
		{
			// Mouse Wheel Up : TargetArmLength Shorter, Mouse Wheel Down : TargetArmLength Longer
			const float NewArmLength = CameraBoom->TargetArmLength - (ZoomSpeed * Value);
			CameraBoom->TargetArmLength = FMath::Clamp<float>(NewArmLength, ZoomDistance.X, ZoomDistance.Y);
		}
	}
}

void AWIDPlayerController::SetSimpleInputMode(const EInputMode NewInputMode)
{
	switch (NewInputMode)
	{
	case EInputMode::GameOnly:
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
		break;
	case EInputMode::UIOnly:
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		break;
	case EInputMode::GameAndUI:
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
		break;
	}
}


void AWIDPlayerController::StartCameraFade()
{
	if (StartFadeScreenTime > 0.0f)
	{
		AWIDPlayerCameraManager* WIDPlayerCameraManager = Cast<AWIDPlayerCameraManager>(PlayerCameraManager);
		if (IsValid(WIDPlayerCameraManager))
		{
			WIDPlayerCameraManager->StartCameraFadeWithUI(1.0f, 0.0f, StartFadeScreenTime, FLinearColor::Black, true);
		}
	}
}