#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "PJS/Characters/IZombie.h"
#include "GenericTeamAgentInterface.h"
#include "Blueprint/UserWidget.h"
#include "CCharacter.generated.h"

UCLASS()
class NAKWON_API ACCharacter
	: public ACharacter
	, public IIZombie
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

	UPROPERTY(VisibleAnywhere, category="Component")
	class UCStatusComponent* Status;

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

	UPROPERTY(VisibleAnywhere, category="Input")
    class UInputAction* IA_Crouch;

	UPROPERTY(VisibleAnywhere, category="Input")
	class UInputAction* IA_Choke;


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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bCrouched = false;

private:
    void Draw();
    void Shoot();

    FTimerHandle coolTimer;

    void CoolTime();

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	struct FDamageData
	{
		float Power;
		class ACharacter* Character;
		class AActor* Causer;

		struct FActionDamageEvent* Event;
	} Damage;

protected:
	virtual void Damaged();

public:
	virtual void End_Damaged() override;

private:
	void Dead();

public:
	void End_Dead() override;

	private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StaminaWidgetClass;

	UPROPERTY()
	UUserWidget* StaminaWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UAnimMontage* ChokeAnimationMontage;

	void OnChoke(const struct FInputActionValue& InVal);

private:
	UFUNCTION()
	void OnZombieAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
