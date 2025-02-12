#include "LSJ/Notifies/CAnimNotifyState_Equip.h"
#include "Global.h"
#include "GlobalComponents/CWeaponComponent.h"
#include "GlobalComponents/CEquipment.h"

FString UCAnimNotifyState_Equip::GetNotifyName() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	UCWeaponComponent* Weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	NullCheck(Weapon);
	NullCheck(Weapon->GetEquipment());

	Weapon->GetEquipment()->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	UCWeaponComponent* Weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	NullCheck(Weapon);
	NullCheck(Weapon->GetEquipment());

	Weapon->GetEquipment()->End_Equip();
}