#include "CProjectileComponent.h"
#include "Global.h"
#include "Components/InputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Weapons/CAttachment_Projectile.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"

UCProjectileComponent::UCProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bAiming)
	{
		FVector CSpawnPoint = me->GetActorLocation();
		FVector FromDir = me->GetActorLocation();
		FVector ToDir = CSpawnPoint;
		FVector LaunchDirection = UKismetMathLibrary::GetDirectionUnitVector(FromDir, ToDir);

		float Speed = 800.f;
		float Radius = 0.f;
		float MaxSimTime = 2.0f;
		float Frequency = 30.0f;

		FPredictProjectilePathParams PathParams;

		PathParams.StartLocation = CSpawnPoint;
		PathParams.LaunchVelocity = LaunchDirection * Speed;
		PathParams.bTraceWithCollision = true;
		PathParams.ProjectileRadius = Radius;
		PathParams.MaxSimTime = MaxSimTime;
		PathParams.SimFrequency = Frequency;
		PathParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
		PathParams.TraceChannel = ECC_Visibility;

		FPredictProjectilePathResult PathResult;

		if (UGameplayStatics::PredictProjectilePath(me->GetWorld(), PathParams, PathResult))
		{
			for (const FPredictProjectilePathPointData& PointData : PathResult.PathData)
			{
				DrawDebugSphere(me->GetWorld(), PointData.Location, 5.0f, 12, FColor::Red, false, 1.0f);
			}
		}
	}
}

void UCProjectileComponent::Draw()
{
	bAiming = true;
}

void UCProjectileComponent::Shoot()
{
	if (!bAiming)
	{
		FVector CSpawnPoint = me->GetActorLocation();
		FVector FromDir = me->GetActorLocation();
		FVector ToDir = CSpawnPoint;
		FVector LaunchDirection = UKismetMathLibrary::GetDirectionUnitVector(FromDir, ToDir);

		float Speed = 800.f;
		float Radius = 5.0f;
		float MaxSimTime = 2.0f;
		float Frequency = 30.0f;

		FPredictProjectilePathParams PathParams;

		PathParams.StartLocation = CSpawnPoint;
		PathParams.LaunchVelocity = LaunchDirection * Speed;
		PathParams.bTraceWithCollision = true;
		PathParams.ProjectileRadius = Radius;
		PathParams.MaxSimTime = MaxSimTime;
		PathParams.SimFrequency = Frequency;
		PathParams.DrawDebugType = EDrawDebugTrace::None;
		PathParams.TraceChannel = ECC_Visibility;


		FPredictProjectilePathResult PathResult;

		if (UGameplayStatics::PredictProjectilePath(me->GetWorld(), PathParams, PathResult))
		{
			ACAttachment_Projectile* SpawnedProjectile = GetWorld()->SpawnActor<ACAttachment_Projectile>(ACAttachment_Projectile::StaticClass(), CSpawnPoint, FRotator::ZeroRotator);

			if (SpawnedProjectile)
			{

				UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(SpawnedProjectile->GetComponentByClass(UStaticMeshComponent::StaticClass()));

				if (MeshComponent) {

					MeshComponent->SetSimulatePhysics(true);
					MeshComponent->SetPhysicsLinearVelocity(LaunchDirection * Speed, false);
				}
			}
		}

		bAiming = false;
	}
}
