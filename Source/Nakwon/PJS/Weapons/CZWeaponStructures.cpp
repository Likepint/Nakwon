#include "PJS/Weapons/CZWeaponStructures.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CZStateComponent.h"
#include "PJS/Components/CZMovementComponent.h"
#include "Animation/AnimMontage.h"

void FZDoActionData::DoAction(ACharacter * InOwner)
{
	UCZMovementComponent* movement = CHelpers::GetComponent<UCZMovementComponent>(InOwner);

	if (!!movement)
	{
		if (bFixedCamera)
			movement->EnableFixedCamera();

		if (bCanMove == false)
			movement->Stop();
	}

	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}

void FZDoActionData::PlayEffect(UWorld * InWorld, const FVector & InLocation)
{
	NullCheck(Effect);

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(InLocation);

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

void FZDoActionData::PlayEffect(UWorld * InWorld, const FVector & InLocation, const FRotator & InRotation)
{
	NullCheck(Effect);

	FTransform transform;
	transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
	transform.SetScale3D(EffectScale);

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

///////////////////////////////////////////////////////////////////////////////

void FZHitData::SendDamage(ACharacter * InAttacker, AActor * InAttackCauser, ACharacter * InOther)
{
	FZActionDamageEvent e;
	e.HitData = this;

	InOther->TakeDamage(Power, e, InAttacker->GetController(), InAttackCauser);
}

void FZHitData::PlayMontage(ACharacter * InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}

void FZHitData::PlayHitStop(UWorld * InWorld)
{
	TrueCheck(FMath::IsNearlyZero(StopTime));


	TArray<ACharacter*> characters;
	for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		ACharacter* character = Cast<ACharacter>(actor);

		if (!!character)
		{
			character->CustomTimeDilation = 1e-3f;

			characters.Add(character);
		}
	}


	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([=]()
		{
			for (ACharacter* character : characters)
				character->CustomTimeDilation = 1;
		});

	FTimerHandle timerHandle;
	InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime, false);
}

void FZHitData::PlaySoundWave(ACharacter * InOwner)
{
	NullCheck(Sound);

	UWorld* world = InOwner->GetWorld();
	FVector location = InOwner->GetActorLocation();

	UGameplayStatics::SpawnSoundAtLocation(world, Sound, location);
}

void FZHitData::PlayEffect(UWorld * InWorld, const FVector & InLocation)
{
	NullCheck(Effect);

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(InLocation);

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

void FZHitData::PlayEffect(UWorld * InWorld, const FVector & InLocation, const FRotator & InRotation)
{
	NullCheck(Effect);

	FTransform transform;
	transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
	transform.SetScale3D(EffectScale);

	CHelpers::PlayEffect(InWorld, Effect, transform);
}
