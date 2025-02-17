#pragma once

#include "CoreMinimal.h"
#include "Weapons/CAttachment.h"
#include "CAttachment_Projectile.generated.h"

UCLASS()
class NAKWON_API ACAttachment_Projectile : public ACAttachment
{
	GENERATED_BODY()


public:
	ACAttachment_Projectile();

public:
	virtual void BeginPlay() override;

public:
	virtual void OnBeginEquip_Implementation() override;;
	virtual void OnUnequip_Implementation() override;;


public:
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, Category = Collision)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UStaticMeshComponent* MeshComp;

public:
	void Shoot();

public:
	float InitialSpeed = 0.f;
	FVector direction;
};