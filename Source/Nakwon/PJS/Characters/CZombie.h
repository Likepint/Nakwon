#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/IZombie.h"
#include "GenericTeamAgentInterface.h"
#include "CZombie.generated.h"

UCLASS()
class NAKWON_API ACZombie
	: public ACharacter
	, public IIZombie
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component")
	class UCRandSetComponent* RandSet;

public:
	ACZombie();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void Initialize();

	void SetAnimInst();

	void SetComponents();

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void Hitted();

public:
	virtual void End_Damaged() override;

private:
	void Dead();

public:
	void End_Dead() override;

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

	int32 GetIndex() { return Index; }

private:
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> animInstances;

	bool Gender = FMath::RandBool();

	int32 Index = FMath::RandRange(0, 2);
};
