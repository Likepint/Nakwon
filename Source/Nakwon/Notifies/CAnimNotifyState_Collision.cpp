#include "Notifies/CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CAttachment.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	NullCheck(weapon);
	NullCheck(weapon->GetAttachment());

	weapon->GetAttachment()->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	NullCheck(weapon);
	NullCheck(weapon->GetAttachment());

	weapon->GetAttachment()->OffCollisions();
}
