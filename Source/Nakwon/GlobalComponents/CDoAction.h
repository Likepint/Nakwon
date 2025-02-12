#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalComponents/CWeaponStructures.h"
#include "CDoAction.generated.h"


UCLASS(Abstract)
class NAKWON_API UCDoAction : public UObject
{
	GENERATED_BODY()

public:
	UCDoAction();

public:
	virtual void BeginPlay
	(
		class ACAttachment* InAttachment,
		class UCEquipment* InEquipment,
		class ACharacter* InOwner,
		const TArray<FDoActionData>& InDoActionData,
		const TArray<FHitData>& InHitData
	);
	virtual void Tick(float InDeltaTime) {}

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
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }
	FORCEINLINE bool GetInAction() { return bInAction; }

public:
	UFUNCTION()
	virtual void OnAttachmentBeginCollision() { }

	UFUNCTION()
	virtual void OnAttachmentEndCollision() { }

	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) { }

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther) { }

// DoAction_Combo 등의 자식들이 접근
protected:

	bool bInAction;

	// Action 시작 여부
	bool bBeginAction;

	class ACharacter* OwnerCharacter;
	class UWorld* World; // Object라 월드 없어서 Owner꺼 씀

	class UCMovementComponent* Movement;
	class UCStateComponent* State;

	TArray<FDoActionData> DoActionDatas;
	TArray<FHitData> HitDatas;
};
