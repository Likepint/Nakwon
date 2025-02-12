#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Particles/ParticleSystem.h"
#include "Engine/DamageEvents.h"
#include "CWeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()

public:	
	// 장착모션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	// Montage 플레이 속도
	UPROPERTY(EditAnywhere)
	float PlayRate= 1.f;

	// 장착 동작 중에 이동할 수 있냐 없냐
	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	// BS 1D 2D ?
	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;

public:
	void DoAction(class ACharacter* InOwner);
};

USTRUCT()
struct FDoActionData
{
	GENERATED_BODY()

public:	
	// 장착모션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	// Montage 플레이 속도
	UPROPERTY(EditAnywhere)
	float PlayRate= 1.f;

	// 장착 동작 중에 이동할 수 있냐 없냐
	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	// DoAction 중 Mouse 돌릴 수 있냐 없냐
	UPROPERTY(EditAnywhere)
	bool bFixedCamera;

	UPROPERTY(EditAnywhere)
	class UFXSystemAsset* Effect;
	
	UPROPERTY(EditAnywhere)
	FVector EffectLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	FVector EffectScale = FVector::OneVector;

public:
	void DoAction(class ACharacter* InOwner);
};

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1;

	UPROPERTY(EditAnywhere)
	float Power;

	UPROPERTY(EditAnywhere)
	float Launch = 100;

	UPROPERTY(EditAnywhere)
	float StopTime=100;

	UPROPERTY(EditAnywhere)
	class USoundWave* Sound;

	UPROPERTY(EditAnywhere)
	class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
	FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector EffectScale = FVector::OneVector;

public:
	void SendDamage(class ACharacter* InAttacker, AActor* InAttackCauser, class ACharacter* InOther);
	void PlayMontage(class ACharacter* InOwner);
	void PlayHitStop(UWorld* InWorld);
	void PlaySoundWave(class ACharacter* InOwner);
	void PlayEffect(UWorld* InWorld, const FVector& InLocation);
	void PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator* InRotator);
};

USTRUCT()
struct FActionDamageEvent
	: public FDamageEvent
{
	GENERATED_BODY()

public:
	FHitData* HitData;
};

UCLASS()
class NAKWON_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
	
};