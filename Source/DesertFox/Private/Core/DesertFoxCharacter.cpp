// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/DesertFoxCharacter.h"
#include "Core/DesertFoxMovementComponent.h"
#include "Core/DesertFoxPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADesertFoxCharacter::ADesertFoxCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDesertFoxMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 270.0f, 0.0f);
		GetCharacterMovement()->JumpZVelocity = 600.f;
		GetCharacterMovement()->AirControl = 0.0f;
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	if (CameraBoom)
	{
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 300.0f;
		CameraBoom->bUsePawnControlRotation = true;
	}

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	if (FollowCamera)
	{
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->bUsePawnControlRotation = false;
	}
}

void ADesertFoxCharacter::Run()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->IsWalking())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::Running);
		}
	}
}

void ADesertFoxCharacter::SlowWalk()
{
	UDesertFoxMovementComponent* DesertFoxMovement= Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->IsWalking())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::SlowWalking);
		}
	}
}

void ADesertFoxCharacter::RestoreMovementState()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		DesertFoxMovement->RestoreMovmenetState();
	}
}

void ADesertFoxCharacter::StartJump()
{
	UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(GetCharacterMovement());
	if (DesertFoxMovement)
	{
		if (DesertFoxMovement->IsWalking())
		{
			DesertFoxMovement->SetMovementState(EDesertFoxMovementState::Jumping);

			if (LatentJumpTime > 0.0f)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADesertFoxCharacter::RealJump, LatentJumpTime, false);
			}
			else
			{
				RealJump();
			}
		}
	}
}

void ADesertFoxCharacter::RealJump()
{
	Jump();
}

void ADesertFoxCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	RestoreMovementState();
}