#include "PJS/Characters/CZombie.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CAnimInstance_Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PJS/Components/CRandSetComponent.h"

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
}

void ACZombie::SetAnimInst()
{
	ConstructorHelpers::FClassFinder<UCAnimInstance_Zombie> MAnim(L"/Script/Engine.AnimBlueprint'/Game/PJS/ABP_CAnimInstance_Zombie_M.ABP_CAnimInstance_Zombie_M_C'");
	animInstances.Add(MAnim.Class);

	ConstructorHelpers::FClassFinder<UCAnimInstance_Zombie> WAnim(L"/Script/Engine.AnimBlueprint'/Game/PJS/ABP_CAnimInstance_Zombie_W.ABP_CAnimInstance_Zombie_W_C'");
	animInstances.Add(WAnim.Class);
}

void ACZombie::SetComponents()
{
	RandSet = CreateDefaultSubobject<UCRandSetComponent>("RandSetComponent");

}
