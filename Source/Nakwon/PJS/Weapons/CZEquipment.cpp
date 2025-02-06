#include "PJS/Weapons/CZEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CZMovementComponent.h"
#include "PJS/Components/CZStateComponent.h"
#include "PJS/Weapons/CZEquipment.h"

void UCZEquipment::BeginPlay(ACharacter * InOwner, const FZEquipmentData & InData)
{
	OwnerCharacter = InOwner;
	Data = InData;

	Movement = CHelpers::GetComponent<UCZMovementComponent>(InOwner);
	State = CHelpers::GetComponent<UCZStateComponent>(InOwner);
}

void UCZEquipment::Equip_Implementation()
{
	State->SetEquipMode();

	if (OnEquipmentEquip.IsBound())
		OnEquipmentEquip.Broadcast();

	if (Data.bCanMove == false)
		Movement->Stop();

	if (Data.bUseControlRotation)
		Movement->EnableControlRotation();

	if (!!Data.Montage)
	{
		OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRate);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void UCZEquipment::Begin_Equip_Implementation()
{
	bBeginEquip = true;

	if (OnEquipmentBeginEquip.IsBound())
		OnEquipmentBeginEquip.Broadcast();
}

void UCZEquipment::End_Equip_Implementation()
{
	bBeginEquip = false;
	bEquipped = true;

	Movement->Move();
	State->SetIdleMode();
}

void UCZEquipment::Unequip_Implementation()
{
	bEquipped = false;
	Movement->DisableControlRotation();

	if (OnEquipmentUnequip.IsBound())
		OnEquipmentUnequip.Broadcast();
}
