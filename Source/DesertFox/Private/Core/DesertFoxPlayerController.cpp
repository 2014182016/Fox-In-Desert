// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DesertFoxPlayerController.h"
#include "Core/DesertFoxCharacter.h"

void ADesertFoxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	// {{ BindAxis
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ADesertFoxPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ADesertFoxPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &ADesertFoxPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &ADesertFoxPlayerController::LookUp);
	// }} BindAxis

	// {{ BindAction
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ADesertFoxPlayerController::StartJump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ADesertFoxPlayerController::StopJump);
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ADesertFoxPlayerController::StartRun);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &ADesertFoxPlayerController::StopRun);
	InputComponent->BindAction(TEXT("SlowWalk"), IE_Pressed, this, &ADesertFoxPlayerController::StartSlowWalk);
	InputComponent->BindAction(TEXT("SlowWalk"), IE_Released, this, &ADesertFoxPlayerController::StopSlowWalk);
	InputComponent->BindAction(TEXT("LookLeft"), IE_Pressed, this, &ADesertFoxPlayerController::StartLookLeft);
	InputComponent->BindAction(TEXT("LookLeft"), IE_Released, this, &ADesertFoxPlayerController::StopLookLeft);
	InputComponent->BindAction(TEXT("LookRight"), IE_Pressed, this, &ADesertFoxPlayerController::StartLookRight);
	InputComponent->BindAction(TEXT("LookRight"), IE_Released, this, &ADesertFoxPlayerController::StopLookRight);
	// }} BindAction
}

void ADesertFoxPlayerController::MoveForward(const float Value)
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter) && Value != 0.0f)
	{
		FRotator Rot = bUsePawnControlRotation ? GetControlRotation() : DesertFoxCharacter->GetActorForwardVector().Rotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::X);

		DesertFoxCharacter->AddMovementInput(Dir, Value);
	}
}

void ADesertFoxPlayerController::MoveRight(const float Value)
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter) && Value != 0.0f)
	{
		FRotator Rot = bUsePawnControlRotation ? GetControlRotation() : DesertFoxCharacter->GetActorForwardVector().Rotation();
		FVector Dir = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);

		DesertFoxCharacter->AddMovementInput(Dir, Value);
	}
}

void ADesertFoxPlayerController::Turn(const float Value)
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter) && Value != 0.0f)
	{
		DesertFoxCharacter->AddControllerYawInput(Value * MouseSensitivity * GetWorld()->DeltaTimeSeconds);
	}
}

void ADesertFoxPlayerController::LookUp(const float Value)
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter) && Value != 0.0f)
	{
		DesertFoxCharacter->AddControllerPitchInput(Value * MouseSensitivity * GetWorld()->DeltaTimeSeconds);
	}
}

void ADesertFoxPlayerController::StartJump()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->StartJump();
	}
}

void ADesertFoxPlayerController::StopJump()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->StopJumping();
	}
}

void ADesertFoxPlayerController::StartRun()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->Run();
	}
}

void ADesertFoxPlayerController::StopRun()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->RestoreMovementState();
	}
}

void ADesertFoxPlayerController::StartSlowWalk()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->SlowWalk();
	}
}

void ADesertFoxPlayerController::StopSlowWalk()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->RestoreMovementState();
	}
}

void ADesertFoxPlayerController::StartLookLeft()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->StartLookLeft();
	}
}

void ADesertFoxPlayerController::StopLookLeft()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->StopLookLeft();
	}
}

void ADesertFoxPlayerController::StartLookRight()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->StartLookRight();
	}
}

void ADesertFoxPlayerController::StopLookRight()
{
	ADesertFoxCharacter* const DesertFoxCharacter = Cast<ADesertFoxCharacter>(GetCharacter());
	if (IsValid(DesertFoxCharacter))
	{
		DesertFoxCharacter->StopLookRight();
	}
}