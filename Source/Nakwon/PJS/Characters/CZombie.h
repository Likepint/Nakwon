#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CZombie.generated.h"

UCLASS(NotBlueprintable)
class NAKWON_API ACZombie : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCRandSetComponent* RandSet;

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
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> GetAnimInstances() { return animInstances; }

	bool GetGender() { return Gender; }

private:
	TArray<TSubclassOf<class UCAnimInstance_Zombie>> animInstances;

	bool Gender = FMath::RandBool();
};
