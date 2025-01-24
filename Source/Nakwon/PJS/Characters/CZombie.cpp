#include "PJS/Characters/CZombie.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PJS/Components/CRandSetComponent.h"

ACZombie::ACZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	Initialize();

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

void ACZombie::SetComponents()
{
	RandSet = CreateDefaultSubobject<UCRandSetComponent>("RandSetComponent");

}
