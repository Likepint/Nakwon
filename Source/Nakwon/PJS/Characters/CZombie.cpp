#include "PJS/Characters/CZombie.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CAnimInstance_Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PJS/Components/CRandSetComponent.h"
#include "Components/CStateComponent.h"
#include "LSJ/Components/CMovementComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CWeaponStructures.h"

ACZombie::ACZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	Initialize();

	SetAnimInst();

	SetComponents();

}

void ACZombie::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 50;

	//if (FMath::RandBool()) State->SetSleepMode();
	//else State->SetIdleMode();

	State->OnStateTypeChanged.AddDynamic(this, &ACZombie::OnStateTypeChanged);
}

void ACZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACZombie::Initialize()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACZombie::SetAnimInst()
{
	ConstructorHelpers::FClassFinder<UCAnimInstance_Zombie> Anim(L"/Script/Engine.AnimBlueprint'/Game/PJS/BP_CAnimInstance_Zombie.BP_CAnimInstance_Zombie_C'");
	if (Anim.Succeeded())
		GetMesh()->SetAnimInstanceClass(Anim.Class);
}

void ACZombie::SetComponents()
{
	RandSet = CreateDefaultSubobject<UCRandSetComponent>("RandSet");

	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCMovementComponent>(this, &Movement, "Movement");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");

}

float ACZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Power = damage;
	Damage.Character = Cast<ACharacter>(EventInstigator->GetPawn());
	Damage.Causer = DamageCauser;
	Damage.Event = (FActionDamageEvent*)&DamageEvent;

	State->SetDamagedMode();

	return damage;
}

void ACZombie::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Damaged: Damaged(); break;
		case EStateType::Dead: Dead(); break;
	}
}

void ACZombie::Damaged()
{
	//Apply Damage
	{
		Status->Damage(Damage.Power);
		Damage.Power = 0;
	}

	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		data->PlayMontage(this);
		data->PlayHitStop(GetWorld());
		data->PlaySoundWave(this);
		data->PlayEffect(GetWorld(), GetActorLocation(), GetActorRotation());

		if (Status->IsDead() == false)
		{
			FVector start = GetActorLocation();
			FVector target = Damage.Character->GetActorLocation();
			FVector direction = target - start;
			direction.Normalize();

			LaunchCharacter(-direction * data->Launch, false, false);
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
		}
	}

	if (Status->IsDead())
	{
		State->SetDeadMode();

		return;
	}

	Damage.Character = nullptr;
	Damage.Causer = nullptr;
	Damage.Event = nullptr;
}

void ACZombie::End_Damaged()
{
	State->SetIdleMode();
}

void ACZombie::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Montage->PlayDeadMode();
}

void ACZombie::End_Dead()
{

}
