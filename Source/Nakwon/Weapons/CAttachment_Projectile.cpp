#include "Weapons/CAttachment_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h" 
#include "Components/ActorComponent.h" 

#include "GameFramework/ProjectileMovementComponent.h"

ACAttachment_Projectile::ACAttachment_Projectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->SetCollisionProfileName(FName("BlockAll"));
    CollisionComp->SetSphereRadius(20.f);
    SetRootComponent(CollisionComp);

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComp->SetRelativeScale3D(FVector(0.5));

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
    MovementComp->SetUpdatedComponent(CollisionComp);
    MovementComp->InitialSpeed = 7000.f;
    MovementComp->MaxSpeed = 7000.f;
    MovementComp->bShouldBounce = true;
    MovementComp->Bounciness = 0.3f;
    
    InitialLifeSpan = 0.3f;
}

void ACAttachment_Projectile::BeginPlay()
{
    Super::BeginPlay();

    CollisionComp->SetVisibility(false);

    AttachTo("Projectile");
    
    CollisionComp->SetVisibility(true);
    MovementComp->Deactivate();
}

void ACAttachment_Projectile::OnBeginEquip_Implementation() 
{
    AttachTo("Projectile");
}

void ACAttachment_Projectile::OnUnequip_Implementation() 
{
    AttachTo("Projectile");
}

void ACAttachment_Projectile::Shoot()
{
    InitialSpeed = MovementComp->InitialSpeed;
    direction = MovementComp->ConstrainDirectionToPlane(direction);
    FVector velocity = InitialSpeed * direction;
    
    if (MovementComp)
    {
        MovementComp->Velocity = velocity;
        MovementComp->SetActive(true, true);
    }
}
