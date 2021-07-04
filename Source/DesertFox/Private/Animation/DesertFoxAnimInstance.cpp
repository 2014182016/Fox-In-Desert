// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DesertFoxAnimInstance.h"
#include "Core/DesertFoxCharacter.h"
#include "Core/DesertFoxMovementComponent.h"

void UDesertFoxAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ADesertFoxCharacter* DesertFoxCharacter = Cast<ADesertFoxCharacter>(TryGetPawnOwner());
	if (IsValid(DesertFoxCharacter))
	{
		UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(DesertFoxCharacter->GetCharacterMovement());
		if (DesertFoxMovement)
		{
			bIsInAir = DesertFoxMovement->IsFalling();
			bIsSlowWalking = DesertFoxMovement->IsSlowWalking();
			bIsJumping = DesertFoxMovement->IsJumping();
		}

		CurrentSpeed = DesertFoxCharacter->GetVelocity().Size();
	}
}