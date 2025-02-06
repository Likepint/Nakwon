#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PJS/Weapons/CZWeaponStructures.h"
#include "CZEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FZEquipmentEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FZEquipmentBeginEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FZEquipmentUnequip);

UCLASS()
class NAKWON_API UCZEquipment : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }

public:
	void BeginPlay(class ACharacter* InOwner, const FZEquipmentData& InData);

public:
	UFUNCTION(BlueprintNativeEvent)
	void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Unequip();
	void Unequip_Implementation();

public:
	FZEquipmentBeginEquip OnEquipmentEquip;
	FZEquipmentBeginEquip OnEquipmentBeginEquip;
	FZEquipmentUnequip OnEquipmentUnequip;

protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* OwnerCharacter;

private:
	FZEquipmentData Data;

private:
	class UCZMovementComponent* Movement;
	class UCZStateComponent* State;

private:
	bool bBeginEquip;
	bool bEquipped;
};
