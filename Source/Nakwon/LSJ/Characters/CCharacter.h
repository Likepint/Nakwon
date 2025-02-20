#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CCharacter.generated.h"

UCLASS()
class NAKWON_API ACCharacter
	: public ACharacter
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 TeamID = 1;
	
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UCameraComponent* Camera;

private:
    UPROPERTY(EditDefaultsOnly)
    class USphereComponent* CSpawnPoint;

public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, category="Component")
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

	UPROPERTY(VisibleAnywhere, category="Input")
    class UInputAction* IA_Projectile;

private:
    UPROPERTY(EditAnywhere, Category = "Projectile")
    TSubclassOf<class ACAttachment_Projectile> Projectile;


public:
	ACCharacter();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool bThrow = false;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool bCanShoot = true;

private:
    void Draw();
    void Shoot();

    FTimerHandle coolTimer;

    void CoolTime();
};
