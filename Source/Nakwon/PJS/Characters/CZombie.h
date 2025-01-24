#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CZombie.generated.h"

UCLASS()
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

	void SetComponents();
};
