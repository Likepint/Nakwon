#include "PJS/Characters/CZombie.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CAnimInstance_Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PJS/Components/CRandSetComponent.h"
#include "Components/CStateComponent.h"
#include "PJS/Components/CZMovementComponent.h"
#include "Components/CWeaponComponent.h"
//#include "PJS/Components/CZMontageComponent.h"

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

}

void ACZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
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

	State = CreateDefaultSubobject<UCStateComponent>("State");
	Movement = CreateDefaultSubobject<UCMovementComponent>("Movement");
	Weapon = CreateDefaultSubobject<UCWeaponComponent>("Weapon");

}

float ACZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//Damage.Power = damage;
	//Damage.Character = Cast<ACharacter>(EventInstigator->GetPawn());
	//Damage.Causer = DamageCauser;
	//Damage.Event = (FZActionDamageEvent*)&DamageEvent;

	//State->SetHittedMode();

	return damage;
}

//void ACZombie::OnStateTypeChanged(EZState InPrevType, EZState InNewType)
//{
//	/*switch (InNewType)
//	{
//		case EZState::dama: Hitted(); break;
//		case EZState::Dead: Dead(); break;
//	}*/
//}

void ACZombie::Hitted()
{
	//Apply Damage
	//{
	//	Status->Damage(Damage.Power);
	//	Damage.Power = 0;
	//}

	////Change Color
	//{
	//	Change_Color(this, FLinearColor::Red);

	//	FTimerDelegate timerDelegate;
	//	timerDelegate.BindUFunction(this, "RestoreColor");

	//	GetWorld()->GetTimerManager().SetTimer(RestoreColor_TimerHandle, timerDelegate, 0.2f, false);
	//}	

	//if (!!Damage.Event && !!Damage.Event->HitData)
	//{
	//	FZHitData* data = Damage.Event->HitData;

	//	data->PlayMontage(this);
	//	data->PlayHitStop(GetWorld());
	//	data->PlaySoundWave(this);
	//	data->PlayEffect(GetWorld(), GetActorLocation(), GetActorRotation());

	//	if (Status->IsDead() == false)
	//	{
	//		FVector start = GetActorLocation();
	//		FVector target = Damage.Character->GetActorLocation();
	//		FVector direction = target - start;
	//		direction.Normalize();

	//		LaunchCharacter(-direction * data->Launch, false, false);
	//		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
	//	}
	//}

	//if (Status->IsDead())
	//{
	//	State->SetDeadMode();

	//	return;
	//}

	//Damage.Character = nullptr;
	//Damage.Causer = nullptr;
	//Damage.Event = nullptr;
}

void ACZombie::End_Damaged()
{
	//State->SetIdleMode();
}

void ACZombie::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Montage->PlayDeadMode();
}

void ACZombie::End_Dead()
{

}
