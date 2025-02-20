#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LSJ/Characters/CCharacter.h"
#include "CProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UCProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCProjectileComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UPROPERTY()
	ACCharacter* me;

public:
	void Draw();
	void Shoot();

	bool bAiming;
};
