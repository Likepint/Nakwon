#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PJS/Weapons/CZWeaponStructures.h"
#include "CZDoAction.generated.h"

UCLASS(Abstract)
class NAKWON_API UCZDoAction : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }
	FORCEINLINE bool GetInAction() { return bInAction; }

public:
	UCZDoAction();

	virtual void BeginPlay
	(
		class ACZAttachment* InAttachment,
		class UCZEquipment* InEquipment,
		class ACharacter* InOwner,
		const TArray<FZDoActionData>& InDoActionDatas,
		const TArray<FZHitData>& InHitDatas
	);
	virtual void Tick(float InDeltaTime) { }

public:
	virtual void DoAction();
	virtual void Begin_DoAction();
	virtual void End_DoAction();

public:
	UFUNCTION()
	virtual void OnBeginEquip() { }

	UFUNCTION()
	virtual void OnUnequip() { }

public:
	UFUNCTION()
	virtual void OnAttachmentBeginCollision() { }

	UFUNCTION()
	virtual void OnAttachmentEndCollision() { }

	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) { }

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther) { }


protected:
	bool bInAction;
	bool bBeginAction;

	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UCZMovementComponent* Movement;
	class UCZStateComponent* State;

	TArray<FZDoActionData> DoActionDatas;
	TArray<FZHitData> HitDatas;
};

