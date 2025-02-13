#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

UCLASS()
class NAKWON_API ACCharacter : public ACharacter
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleAnywhere, category="Component")
	class UCMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere, category="Component")
	class UCStateComponent* State;

	UPROPERTY(VisibleAnywhere, category = "Component")
	class UCWeaponComponent* Weapon;

private:
	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputMappingContext* IMC_Default;

	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputAction* IA_Movement;

	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputAction* IA_Look;

	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputAction* IA_Run;

	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputAction* IA_Bat;

	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputAction* IA_Attack;

public:
	ACCharacter();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
};
