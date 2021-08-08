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
	void PlayAllEffect(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const;
	void PlayParticle(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const;
	void PlayDecal(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const;
	void PlaySound(const UObject* WorldContextObject, const AActor* const Target, const FVector& Location) const;

public:
	/** Int type of surface type of corresponding physical material. */
	UPROPERTY(EditDefaultsOnly)
		int32 SurfaceType;
	/** Sound to play at footstep */
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* SoundCue;
	/** Decal to play at footstep */
	UPROPERTY(EditDefaultsOnly, Category = "Decal")
		class UMaterialInstance* DecalMaterial;
	/** Whether to use niagara particle */
	UPROPERTY(EditDefaultsOnly, Category = "Particle")
		bool bUseNiagaraParitlce;
	/** Particle to play at footstep */
	UPROPERTY(EditDefaultsOnly, Category = "Particle", meta = (EditCondition = "!bUseNiagaraParitlce"))
		class UParticleSystem* Particle;
	/** Niagara particle to play at footstep */
	UPROPERTY(EditDefaultsOnly, Category = "Particle", meta = (EditCondition = "bUseNiagaraParitlce"))
		class UNiagaraSystem* NiagaraParticle;
	/** If there is a decal material, specify the decal size */
	UPROPERTY(EditDefaultsOnly, Category = "Decal")
		FVector DecalSize;
	/** If there is a decal material, specify the decal life span */
	UPROPERTY(EditDefaultsOnly, Category = "Decal")
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

protected:
	/** Overwrite footstep info according to the properties currently specified in notify */
	FFoostepInfo OverwriteFootstepInfo(FFoostepInfo* const InInfo) const;

	/** Use foot position enumeration to return the location of the foot to check floor trace */
	static FVector GetFootLocation(const USkeletalMeshComponent* const MeshComp, const EFootPosition FootPosition);
	
	/** Spawn decals and particles to each foot position as many as the FootPositionList */
	void SpawnDecalsAndParticlesAtFootPositon(class AWIDCharacter* WIDCharacter, FFoostepInfo* const InInfo) const;

protected:
	/** Information list to be used in accordance with floor physical material when calling notify */
	UPROPERTY(EditDefaultsOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		TArray<FFoostepInfo> SoundInfoList;

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
		uint8 bNoPlaySound : 1;

	/** Don't spawn decal */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		uint8 bNoPlayDecal : 1;

	/** Don't spawn particle */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		uint8 bNoPlayParticle : 1;

	/** Spawn decal and particle as much as specified foot position */
	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (AllowPrivateAccess = "true"))
		TArray<EFootPosition> FootPositonList;
};
