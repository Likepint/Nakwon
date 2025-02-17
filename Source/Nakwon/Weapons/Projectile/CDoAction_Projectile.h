#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Projectile.generated.h"

UCLASS()
class NAKWON_API UCDoAction_Projectile : public UCDoAction
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void EnableProjectile() { bEnable = true; }
	FORCEINLINE void DisableProjectile() { bEnable = false; }

public:
	void DoAction() override;
	void Begin_DoAction() override;
	void End_DoAction() override;

public:
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) override;
	void OnAttachmentEndCollision() override;


private:
	int32 Index;

	bool bEnable;
	bool bExist;

private:
	TArray<class ACharacter*> Hitted;


public:
	void ProjectileShooting();
};
