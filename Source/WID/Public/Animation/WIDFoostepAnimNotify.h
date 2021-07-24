// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WIDTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "WIDFoostepAnimNotify.generated.h"

/** Enumeration of the position of each foot */
UENUM()
enum class EFootPosition : uint8
{
	ForelegLeft,
	ForelegRight,
	HindlegLeft,
	HindlegRight,
};

/** Collection of information to use at footstep */
USTRUCT()
struct FFoostepInfo
{
	GENERATED_USTRUCT_BODY()

public:
	void PlayEffect(const AActor* const Context, const FVector& Location) const;

public:
	/** Int type of surface type of corresponding physical material. */
	UPROPERTY(EditDefaultsOnly)
		int32 SurfaceType;
	/** Sound to play at footstep */
	UPROPERTY(EditDefaultsOnly)
		class USoundCue* SoundCue;
	/** Decal to play at footstep */
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstance* DecalMaterial;
	/** Whether to use niagara particle */
	UPROPERTY(EditDefaultsOnly)
		bool bUseNiagaraParitlce;
	/** Particle to play at footstep */
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "!bUseNiagaraParitlce"))
		class UParticleSystem* Particle;
	/** Niagara particle to play at footstep */
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bUseNiagaraParitlce"))
		class UNiagaraSystem* NiagaraParticle;
	/** If there is a decal material, specify the decal size */
	UPROPERTY(EditDefaultsOnly)
		FVector DecalSize;
	/** If there is a decal material, specify the decal life span */
	UPROPERTY(EditDefaultsOnly)
		float DecalLifeSpan;
};

/**
 * 
 */
UCLASS()
class WID_API UWIDFoostepAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// {{ UAnimNotify Interface
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	// }} UAnimNotify Interface

	/** Overwrite footstep info according to the properties currently specified in notify */
	FFoostepInfo OverwriteFootstepInfo(FFoostepInfo* const InInfo) const;

	/** Use foot position enumeration to return the location of the foot to check floor trace */
	static FVector GetFootLocation(const USkeletalMeshComponent* const MeshComp, const EFootPosition FootPosition);

protected:
	/** Information list to be used in accordance with floor physical material when calling notify */
	UPROPERTY(EditDefaultsOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		TArray<FFoostepInfo> SoundInfoList;

	/** Position of foot to spawn effect */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		EFootPosition FootPosition;

	/** Overwrite sound cue to play at footstep */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		class USoundCue* SoundCue;

	/** Overwrite decal material to play at footstep */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		class UMaterialInstance* DecalMaterial;

	/** Whether to use niagara particle */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		bool bUseNiagaraParitlce;

	/** Overwrite particle to play at footstep */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true", EditCondition = "!bUseNiagaraParitlce"))
		class UParticleSystem* Particle;

	/** Overwrite niagara particle to play at footstep */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true", EditCondition = "bUseNiagaraParitlce"))
		class UNiagaraSystem* NiagaraParticle;

	/** Don't play sound */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		bool bNoPlaySound = false;

	/** Don't spawn decal */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		bool bNoPlayDecal = false;

	/** Don't spawn particle */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		bool bNoPlayParticle = false;
};
