// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DesertFoxAnimInstance.h"
#include "Core/DesertFoxCharacter.h"
#include "Core/DesertFoxMovementComponent.h"
#include "Curves/CurveFloat.h"

void UDesertFoxAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ADesertFoxCharacter* DesertFoxCharacter = Cast<ADesertFoxCharacter>(TryGetPawnOwner());
	if (IsValid(DesertFoxCharacter))
	{
		CurrentSpeed = DesertFoxCharacter->GetVelocity().Size();
		CurrentSpeed2D = DesertFoxCharacter->GetVelocity().Size2D();

		UDesertFoxMovementComponent* DesertFoxMovement = Cast<UDesertFoxMovementComponent>(DesertFoxCharacter->GetCharacterMovement());
		if (DesertFoxMovement)
		{
			bIsInAir = DesertFoxMovement->IsFalling();
			bIsSlowWalking = DesertFoxMovement->IsSlowWalking();
			bIsJumping = DesertFoxMovement->IsJumping();

			if (JumpAnimRateCurve)
			{
				JumpAnimRate = JumpAnimRateCurve->GetFloatValue(DesertFoxMovement->DistanceToFloorWhileFalling);
			}
		}
	}
}