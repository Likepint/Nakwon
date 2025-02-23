#pragma once

#include "CoreMinimal.h"
#include "Weapons/CAttachment.h"
#include "CAttachment_Projectile.generated.h"

UCLASS()
class NAKWON_API ACAttachment_Projectile : public AActor
{
	GENERATED_BODY()


public:
	ACAttachment_Projectile();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float Deltatime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	class UProjectileMovementComponent* projectile;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	class USphereComponent* TestSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	class UStaticMeshComponent* MeshSphere;


	UFUNCTION()
	void OnCSpawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
	
	UPROPERTY(EditAnywhere, Category = "Projectile")
    class UAnimMontage* HitReaction;

	bool bHit = false;

};