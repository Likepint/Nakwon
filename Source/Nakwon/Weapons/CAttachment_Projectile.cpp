#include "Weapons/CAttachment_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h" 
#include "Components/ActorComponent.h" 

#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "../LSJ/Characters/CCharacter.h"

ACAttachment_Projectile::ACAttachment_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	TestSphere = CreateDefaultSubobject<USphereComponent>("TestSphere");
	TestSphere->SetSphereRadius(32.f);
	TestSphere->SetCollisionProfileName(FName("BlockAll"));
	SetRootComponent(TestSphere);

	MeshSphere = CreateDefaultSubobject<UStaticMeshComponent>("MeshSphere");
	MeshSphere->SetRelativeScale3D(FVector(0.4f));
	MeshSphere->SetupAttachment(TestSphere);
	MeshSphere->SetCollisionProfileName(FName("BlockAllDynamic"));


}

void ACAttachment_Projectile::BeginPlay()
{
	Super::BeginPlay();

	TestSphere->SetSimulatePhysics(true);
	MeshSphere->SetSimulatePhysics(false);

	if (auto me = Cast<ACCharacter>(GetOwner()))
	{

	}
}

void ACAttachment_Projectile::OnBeginEquip_Implementation()
{
	AttachTo("Projectile");
}

void ACAttachment_Projectile::OnUnequip_Implementation()
{
	AttachTo("Projectile");
}
