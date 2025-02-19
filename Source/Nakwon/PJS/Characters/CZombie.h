#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "PJS/Characters/IZombie.h"
#include "GenericTeamAgentInterface.h"
#include "CZombie.generated.h"

UCLASS()
class NAKWON_API ACZombie
	: public ACharacter
	, public IIZombie
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component")
	class UCRandSetComponent* RandSet;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component")
	class UCStateComponent* State;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component")
	class UCMovementComponent* Movement;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component")
	class UCStatusComponent* Status;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component")
	class UCWeaponComponent* Weapon;

public:
	ACZombie();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Initialize();

	void SetAnimInst();

	void SetComponents();

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void Damaged();

public:
	virtual void End_Damaged() override;

private:
	void Dead();

public:
	void End_Dead() override;

private:
	struct FDamageData
	{
		float Power;
		class ACharacter* Character;
		class AActor* Causer;

		struct FActionDamageEvent* Event;
	} Damage;

public:
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> GetAnimInstances() { return animInstances; }

	bool GetGender() { return Gender; }

	int32 GetIndex() { return Index; }

private:
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> animInstances;

	bool Gender = FMath::RandBool();

	int32 Index = FMath::RandRange(0, 2);
};
