#include "PJS/Components/CZWeaponComponent.h"
#include "Global.h"
#include "CZStateComponent.h"
#include "GameFramework/Character.h"
#include "PJS/Weapons/CZWeaponAsset.h"
#include "PJS/Weapons/CZWeaponData.h"
#include "PJS/Weapons/CZAttachment.h"
#include "PJS/Weapons/CZEquipment.h"
#include "PJS/Weapons/CZDoAction.h"
//#include "Weapons/CSubAction.h"

UCZWeaponComponent::UCZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCZWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EWeapon::MAX; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter, &Datas[i]);
	}
}

void UCZWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!!GetDoAction())
		GetDoAction()->Tick(DeltaTime);

	//if (!!GetSubAction())
	//	GetSubAction()->Tick(DeltaTime);
}

bool UCZWeaponComponent::IsIdleMode()
{
	return CHelpers::GetComponent<UCZStateComponent>(OwnerCharacter)->IsIdleMode();
}

ACZAttachment * UCZWeaponComponent::GetAttachment()
{
	TrueCheckResult(IsUnarmedMode(), nullptr);
	FalseCheckResult(!!Datas[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetAttachment();
}

UCZEquipment * UCZWeaponComponent::GetEquipment()
{
	TrueCheckResult(IsUnarmedMode(), nullptr);
	FalseCheckResult(!!Datas[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetEquipment();
}

UCZDoAction * UCZWeaponComponent::GetDoAction()
{
	TrueCheckResult(IsUnarmedMode(), nullptr);
	FalseCheckResult(!!Datas[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetDoAction();
}

//UCZSubAction * UCZWeaponComponent::GetSubAction()
//{
//	TrueCheckResult(IsUnarmedMode(), nullptr);
//	FalseCheckResult(!!Datas[(int32)Type], nullptr);
//
//	return Datas[(int32)Type]->GetSubAction();
//}

void UCZWeaponComponent::SetUnarmedMode()
{
	GetEquipment()->Unequip();

	ChangeType(EWeapon::MAX);
}

void UCZWeaponComponent::SetFistMode()
{
	FalseCheck(IsIdleMode());

	SetMode(EWeapon::Fist);
}

void UCZWeaponComponent::SetSwordMode()
{
	FalseCheck(IsIdleMode());

	SetMode(EWeapon::Sword);
}

void UCZWeaponComponent::SetHammerMode()
{
	FalseCheck(IsIdleMode());

	SetMode(EWeapon::Hammer);
}

void UCZWeaponComponent::SetWarpMode()
{
	FalseCheck(IsIdleMode());

	SetMode(EWeapon::Warp);
}

void UCZWeaponComponent::SetAroundMode()
{
	FalseCheck(IsIdleMode());

	SetMode(EWeapon::Around);
}

void UCZWeaponComponent::SetBowMode()
{
	FalseCheck(IsIdleMode());

	SetMode(EWeapon::Bow);
}

void UCZWeaponComponent::SetMode(EWeapon InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)
	{
		GetEquipment()->Unequip();
	}

	if (!!Datas[(int32)InType])
	{
		Datas[(int32)InType]->GetEquipment()->Equip();

		ChangeType(InType);
	}
}

void UCZWeaponComponent::ChangeType(EWeapon InType)
{
	EWeapon prevType = Type;
	Type = InType;

	if (OnWeaponChange.IsBound())
		OnWeaponChange.Broadcast(prevType, InType);
}

void UCZWeaponComponent::DoAction()
{
	if (!!GetDoAction())
		GetDoAction()->DoAction();
}

//void UCZWeaponComponent::SubAction_Pressed()
//{
//	if (!!GetSubAction())
//		GetSubAction()->Pressed();
//}
//
//void UCZWeaponComponent::SubAction_Released()
//{
//	if (!!GetSubAction())
//		GetSubAction()->Released();
//}
