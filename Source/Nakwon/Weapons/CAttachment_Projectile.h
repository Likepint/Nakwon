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
	virtual void OnBeginEquip_Implementation() override;
	virtual void OnUnequip_Implementation() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	class USphereComponent* TestSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	class UStaticMeshComponent* MeshSphere;

};