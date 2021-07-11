// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/********************************************************************************************************************************
 * This Structure was created to assist TOptional of my version in the Reflection System of the UE4.
 * And UHT dosen't recognize UProperty in macro dode, so it has become a form of this structure.
 * For more information, Look at https://answers.unrealengine.com/questions/600163/wrapping-uproperty-with-macro-not-working.html.
 ********************************************************************************************************************************/

#include "CoreMinimal.h"
#include "OptionalWrapper.generated.h"

#define OPTIONAL_WEAPPER_IMPLEMENT(Name, Type) \
		Name() = default; \
		Name(const Type& InValue) \
		{ \
			Value = InValue; \
			bIsSet = true; \
		} \
		Name(const Name& InValue) \
		{ \
			bIsSet = false; \
			if (InValue.IsSet()) \
			{ \
				Value = InValue.GetValue(); \
				bIsSet = true; \
			} \
		} \
		Name& operator=(const Name& InValue) \
		{ \
			if (this != &InValue) \
			{ \
				Reset(); \
				if (InValue.IsSet()) \
				{ \
					Value = InValue.GetValue(); \
					bIsSet = true; \
				} \
			} \
			return *this; \
		} \
		Name& operator=(const Type& InValue) \
		{ \
			if (Value != InValue) \
			{ \
				Reset(); \
				Value = InValue; \
				bIsSet = true; \
			} \
			return *this; \
		} \
		friend bool operator==(const Name& lhs, const Name& rhs) \
		{ \
			if (lhs.IsSet() != rhs.IsSet()) \
			{ \
				return false; \
			} \
			if (!lhs.IsSet()) \
			{ \
				return true; \
			} \
			return lhs.GetValue() == rhs.GetValue(); \
		} \
		friend bool operator!=(const Name& lhs, const Name& rhs) \
		{ \
			return !(lhs == rhs); \
		} \
		static const char* CStr() \
		{ \
			return #Name; \
		} \
		static const TCHAR* TStr() \
		{ \
			return TEXT(#Name); \
		} \
		Type GetValue() const \
		{ \
			if(!bIsSet) \
				UE_LOG(LogTemp, Warning, TEXT("It is an error to call GetValue() on an unset %s"), TStr()); \
			return Value; \
		} \
		FORCEINLINE explicit operator bool() const \
		{ \
			return bIsSet; \
		} 

USTRUCT(BlueprintType)
struct FOptionalBase
{
	GENERATED_USTRUCT_BODY()

public:
	FOptionalBase() { Reset(); }
	~FOptionalBase() { Reset(); }

	FORCEINLINE explicit operator bool() const { return bIsSet; }

public:
	bool IsSet() const { return bIsSet; }
	void Reset() { bIsSet = false; }

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsSet;
};

USTRUCT(BlueprintType)
struct FOptionalBool : public FOptionalBase
{
	GENERATED_USTRUCT_BODY()
	OPTIONAL_WEAPPER_IMPLEMENT(FOptionalBool, bool)

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		bool Value;
};

USTRUCT(BlueprintType)
struct FOptionalInt : public FOptionalBase
{
	GENERATED_USTRUCT_BODY()
	OPTIONAL_WEAPPER_IMPLEMENT(FOptionalInt, int32)

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		int32 Value;
};

USTRUCT(BlueprintType)
struct FOptionalFloat : public FOptionalBase
{
	GENERATED_USTRUCT_BODY()
	OPTIONAL_WEAPPER_IMPLEMENT(FOptionalFloat, float)

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float Value;
};

USTRUCT(BlueprintType)
struct FOptionalVector : public FOptionalBase
{
	GENERATED_USTRUCT_BODY()
	OPTIONAL_WEAPPER_IMPLEMENT(FOptionalVector, FVector)

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FVector Value;
};

USTRUCT(BlueprintType)
struct FOptionalRotator : public FOptionalBase
{
	GENERATED_USTRUCT_BODY()
	OPTIONAL_WEAPPER_IMPLEMENT(FOptionalRotator, FRotator)

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FRotator Value;
};