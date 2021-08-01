// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WIDFoostepAnimNotify.h"
#include "Core/WIDCharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"

FVector UWIDFoostepAnimNotify::GetFootLocation(const USkeletalMeshComponent* const MeshComp, const EFootPosition FootPosition)
{
	if (!MeshComp)
		return FVector::ZeroVector;

	FName BoneName;
	switch (FootPosition)
	{
	case EFootPosition::ForelegLeft:
		BoneName = FName("L-Hand");
		break;
	case EFootPosition::ForelegRight:
		BoneName = FName("R-Hand");
		break;
	case EFootPosition::HindlegLeft:
		BoneName = FName("L-Foot");
		break;
	case EFootPosition::HindlegRight:
		BoneName = FName("R-Foot");
		break;
	default:
		BoneName = FName("Root");
		break;
	}

	return MeshComp->GetBoneLocation(BoneName);
}

void FFoostepInfo::PlayAllEffect(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const
{
	if (!WorldContextObject || !Target)
		return;

	PlayParticle(WorldContextObject, Target, Location);
	PlayDecal(WorldContextObject, Target, Location);
	PlaySound(WorldContextObject, Target, Location);
}

void FFoostepInfo::PlayParticle(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const
{
	if (!WorldContextObject || !Target)
		return;

	if (bUseNiagaraParitlce)
	{
		if (NiagaraParticle)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, NiagaraParticle, Location);
		}
	}
	else
	{
		if (Particle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, Particle, Location);
		}
	}
}

void FFoostepInfo::PlayDecal(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const
{
	if (!WorldContextObject || !Target)
		return;

	if (DecalMaterial)
	{
		// define decal rotation according to character rotation
		const FRotator DecalRotation = FRotator(-90.0f, 90.0f + Target->GetActorRotation().Yaw, 0.0f);
		UGameplayStatics::SpawnDecalAtLocation(WorldContextObject, DecalMaterial, DecalSize, Location, DecalRotation, DecalLifeSpan);
	}
}

void FFoostepInfo::PlaySound(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const
{
	if (!WorldContextObject || !Target)
		return;

	if (SoundCue)
	{
		UGameplayStatics::PlaySoundAtLocation(WorldContextObject, SoundCue, Location);
	}
}

void UWIDFoostepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		AWIDCharacter* WIDCharacter = Cast<AWIDCharacter>(MeshComp->GetOwner());
		if (IsValid(WIDCharacter))
		{
			FHitResult HitResult(ForceInit);
			FVector StartLoc = WIDCharacter->GetActorLocation();
			FVector EndLoc = StartLoc + (FVector::DownVector * WID::CheckFootstepDistance);

			if (WIDCharacter->GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
			{
				int32 SurfaceType = 0;

				if (HitResult.PhysMaterial.IsValid())
				{
					SurfaceType = static_cast<int32>(HitResult.PhysMaterial->SurfaceType);
				}

				FFoostepInfo* const ResultInfo = SoundInfoList.FindByPredicate(
					[SurfaceType](const FFoostepInfo& InInfo) { return InInfo.SurfaceType == SurfaceType; }
				);

				if (ResultInfo)
				{
					FFoostepInfo OverwrittenInfo = OverwriteFootstepInfo(ResultInfo);

					OverwrittenInfo.PlaySound(WIDCharacter->GetWorld(), WIDCharacter, HitResult.Location);
					SpawnDecalsAndParticlesAtFootPositon(WIDCharacter, &OverwrittenInfo);
				}
			}
		}
	}
}

FFoostepInfo UWIDFoostepAnimNotify::OverwriteFootstepInfo(FFoostepInfo* const InInfo) const
{
	FFoostepInfo NewInfo;

	if (InInfo == nullptr)
		return NewInfo;

	NewInfo = (*InInfo);

	if (bNoPlaySound)
	{
		NewInfo.SoundCue = nullptr;
	}
	else if (SoundCue)
	{
		NewInfo.SoundCue = SoundCue;
	}

	if (bNoPlayDecal)
	{
		NewInfo.DecalMaterial = nullptr;
	}
	else if (DecalMaterial)
	{
		NewInfo.DecalMaterial = DecalMaterial;
	}

	if (bNoPlayParticle)
	{
		NewInfo.Particle = nullptr;
		NewInfo.NiagaraParticle = nullptr;
	}
	else
	{
		if (bUseNiagaraParitlce)
		{
			if (NiagaraParticle)
			{
				NewInfo.bUseNiagaraParitlce = bUseNiagaraParitlce;
				NewInfo.NiagaraParticle = NiagaraParticle;
			}
		}
		else
		{
			if (Particle)
			{
				NewInfo.bUseNiagaraParitlce = bUseNiagaraParitlce;
				NewInfo.Particle = Particle;
			}
		}
	}

	return NewInfo;
}

void UWIDFoostepAnimNotify::SpawnDecalsAndParticlesAtFootPositon(class AWIDCharacter* WIDCharacter, FFoostepInfo* const InInfo) const
{
	if (!WIDCharacter || !InInfo)
		return;

	for (const EFootPosition TestFootPositon : FootPositonList)
	{
		FHitResult HitResult(ForceInit);
		FVector StartLoc = GetFootLocation(WIDCharacter->GetMesh(), TestFootPositon) + (WID::CheckFootstepUpDistance * FVector::UpVector);
		FVector EndLoc = StartLoc + (FVector::DownVector * WID::CheckFootstepDistance);

		if (WIDCharacter->GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
		{
			InInfo->PlayDecal(WIDCharacter->GetWorld(), WIDCharacter, HitResult.Location);
			InInfo->PlayParticle(WIDCharacter->GetWorld(), WIDCharacter, HitResult.Location);
		}
	}
}