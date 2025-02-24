#include "PJS/Managers/CZombieFactory.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "PJS/Characters/CZombie.h"

ACZombieFactory::ACZombieFactory()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	SpawnExtent = CreateDefaultSubobject<UBoxComponent>("SpawnExtent");
	SpawnExtent->SetupAttachment(RootComponent);

}

void ACZombieFactory::BeginPlay()
{
	Super::BeginPlay();
	
	MakeZombie();

}

void ACZombieFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACZombieFactory::MakeZombie()
{
	for (int32 i = 0; i < ZombieCount; ++i)
	{
		FTransform transform;
		transform.SetLocation(UKismetMathLibrary::RandomPointInBoundingBox(SpawnExtent->GetComponentLocation(), SpawnExtent->GetScaledBoxExtent()));

		ACZombie* zombie = GetWorld()->SpawnActor<ACZombie>(ZombieFactory, transform);
	}
}
