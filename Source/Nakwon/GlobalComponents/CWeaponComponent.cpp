#include "GlobalComponents/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GlobalComponents/CWeaponAsset.h" 
#include "LSJ/Characters/CCharacter.h"
#include "CStateComponent.h"
#include "GlobalComponents/CWeaponData.h"
#include "GlobalComponents/CAttachment.h"
#include "GlobalComponents/CEquipment.h"
#include "GlobalComponents/CDoAction.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// component Owner 가져오기
	OwnerCharacter = Cast<ACCharacter>(GetOwner());
	for (int32 i = 0; i < (int32)ECWeapon::MAX; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter, &Datas[i]);
	}
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!!GetDoAction())
		GetDoAction()->Tick(DeltaTime);

	FString str = UEnum::GetValueAsName(Type).ToString();

	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, *str);
}

bool UCWeaponComponent::IsIdleMode()
{
	return CHelpers::GetComponent<UCStateComponent>(OwnerCharacter)->IsIdleMode();
}

ACAttachment* UCWeaponComponent::GetAttachment()
{
	TrueCheckResult(IsUnarmedMode(), nullptr);
	FalseCheckResult(!!Datas[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetAttachment();
}

UCEquipment* UCWeaponComponent::GetEquipment()
{
	TrueCheckResult(IsUnarmedMode(), nullptr);
	FalseCheckResult(!!Datas[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetEquipment();
}

UCDoAction* UCWeaponComponent::GetDoAction()
{
	TrueCheckResult(IsUnarmedMode(), nullptr);
	FalseCheckResult(!!Datas[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetDoAction();
}

// Equipment 해제 후 무기 타입 없음(MAX)로 전환
void UCWeaponComponent::SetUnarmedMode()
{
	FalseCheck(IsIdleMode());
	GetEquipment()->Unequip();
	ChangeType(ECWeapon::MAX);
}

// Idle 일 때 무기 타입을 WoodStick으로 전환
void UCWeaponComponent::SetWoodStickMode()
{
	FalseCheck(IsIdleMode());
	SetMode(ECWeapon::WoodStick);
}

// Idle 일 때 무기 타입을 Bat으로 전환
void UCWeaponComponent::SetBatMode()
{
	FalseCheck(IsIdleMode());
	SetMode(ECWeapon::Bat);
}

// Idle 일 때 무기 타입을 Brick으로 전환
void UCWeaponComponent::SetBrickMode()
{
	FalseCheck(IsIdleMode());
	SetMode(ECWeapon::Brick);
}

void UCWeaponComponent::SetMode(ECWeapon InType)
{
	if (Type == InType) {
		SetUnarmedMode(); // 현재 무기랑 동일 타입이면 Unaremd
		return;
	}
	else if (IsUnarmedMode()==false) {
		GetEquipment()->Unequip(); // 무기 장착 상태면 해제
	}
	if(!!Datas[(int32)InType]) {
		Datas[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType); // DA에 해당 에셋 없으면 전환되지 X
	}
}

// Type을 InType으로 변경
void UCWeaponComponent::ChangeType(ECWeapon InType)
{
	ECWeapon prevType = Type;
	Type = InType;
	
	// 변경상태를 브로드캐스트
	if (OnCWeaponChange.IsBound())
		OnCWeaponChange.Broadcast(prevType, Type);
}

void UCWeaponComponent::DoAction()
{
	if (!!GetDoAction())
		GetDoAction()->DoAction();
}