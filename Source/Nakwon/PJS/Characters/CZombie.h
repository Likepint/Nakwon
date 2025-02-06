#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CZStateComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CZombie.generated.h"

UCLASS(NotBlueprintable)
class NAKWON_API ACZombie
	: public ACharacter
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCRandSetComponent* RandSet;

protected:
	//UPROPERTY(VisibleAnywhere)
	//class UCZMontagesComponent* Montages;

	UPROPERTY(VisibleAnywhere)
	class UCZMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere)
	class UCZStateComponent* State;

	//UPROPERTY(VisibleAnywhere)
	//class UCZStatusComponent* Status;


public:
	ACZombie();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Initialize();

	void SetAnimInst();

	void SetComponents();

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UFUNCTION()
	void OnStateTypeChanged(EState InPrevType, EState InNewType);

protected:
	virtual void Hitted();

//public:
//	virtual void End_Hitted() override;

//private:
//	UFUNCTION()
//	void RestoreColor();

private:
	void Dead();

//public:
//	void End_Dead() override;

private:
	struct FDamageData
	{
		float Power;
		class ACharacter* Character;
		class AActor* Causer;

		struct FZActionDamageEvent* Event;
	} Damage;

private:
	FTimerHandle RestoreColor_TimerHandle;

public:
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> GetAnimInstances() { return animInstances; }

	bool GetGender() { return Gender; }

private:
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> animInstances;

	bool Gender = FMath::RandBool();
};
