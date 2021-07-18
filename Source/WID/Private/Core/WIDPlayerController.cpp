// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WIDPlayerController.h"
#include "Core/WIDCharacter.h"
#include "Core/WIDHUD.h"

void AWIDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	// {{ BindAxis
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AWIDPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AWIDPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AWIDPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AWIDPlayerController::LookUp);
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
	// }} BindAction
}

void AWIDPlayerController::MoveForward(const float Value)
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter) && Value != 0.0f)
	{
		FRotator Rot = bUsePawnControlRotation ? GetControlRotation() : WIDCharacter->GetActorForwardVector().Rotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::X);

		WIDCharacter->AddMovementInput(Dir, Value);
	}
}

void AWIDPlayerController::MoveRight(const float Value)
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter) && Value != 0.0f)
	{
		FRotator Rot = bUsePawnControlRotation ? GetControlRotation() : WIDCharacter->GetActorForwardVector().Rotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);

		WIDCharacter->AddMovementInput(Dir, Value);
	}
}

void AWIDPlayerController::Turn(const float Value)
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter) && Value != 0.0f)
	{
		WIDCharacter->AddControllerYawInput(Value * MouseSensitivity * GetWorld()->DeltaTimeSeconds);
	}
}

void AWIDPlayerController::LookUp(const float Value)
{
	AWIDCharacter* const WIDCharacter = Cast<AWIDCharacter>(GetCharacter());
	if (IsValid(WIDCharacter) && Value != 0.0f)
	{
		WIDCharacter->AddControllerPitchInput(Value * MouseSensitivity * GetWorld()->DeltaTimeSeconds);
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
			WIDHUD->UpdateHudEvent(EHudType::PlayerState, EHudEvent::Update);
			WIDHUD->UpdateHudEventWithValue(EHudType::PlayerState, EHudEvent::Visibility, 0);
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