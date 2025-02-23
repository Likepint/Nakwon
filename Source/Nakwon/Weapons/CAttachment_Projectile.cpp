#include "Weapons/CAttachment_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h" 
#include "Components/ActorComponent.h" 

#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "../LSJ/Characters/CCharacter.h"
#include "../PJS/Characters/CZombie_AI.h"

ACAttachment_Projectile::ACAttachment_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	TestSphere = CreateDefaultSubobject<USphereComponent>("TestSphere");
	TestSphere->SetSphereRadius(32.f);
	SetRootComponent(TestSphere);

	MeshSphere = CreateDefaultSubobject<UStaticMeshComponent>("MeshSphere");
	MeshSphere->SetRelativeScale3D(FVector(0.4f));
	MeshSphere->SetupAttachment(TestSphere);
	MeshSphere->SetCollisionProfileName(FName("BlockAllDynamic"));


	MeshSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshSphere->SetCollisionResponseToAllChannels(ECR_Block);


	TestSphere->SetCollisionProfileName(FName("CSpawnPoint"));
}

void ACAttachment_Projectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(1.5f);

	TestSphere->SetSimulatePhysics(false);

	MeshSphere->SetSimulatePhysics(false);

	if (auto me = Cast<ACCharacter>(GetOwner()))
	{

	}
	TestSphere->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment_Projectile::OnCSpawnOverlap);
	TestSphere->OnComponentHit.AddDynamic(this, &ACAttachment_Projectile::OnProjectileHit);

	MeshSphere->SetNotifyRigidBodyCollision(false);
}

void ACAttachment_Projectile::Tick(float Deltatime)
{
	if (!bHit) {
		MeshSphere->AddRelativeRotation(FQuat(FRotator(15, 0, 15)));
	}
}

void ACAttachment_Projectile::OnCSpawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACZombie_AI* zombie = Cast<ACZombie_AI>(OtherActor);
	if (zombie and HitReaction) {
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, "A");
		zombie->PlayAnimMontage(HitReaction);
	}
}

void ACAttachment_Projectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	bHit = true;
}
