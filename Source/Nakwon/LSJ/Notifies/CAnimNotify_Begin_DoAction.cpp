#include "LSJ/Notifies/CAnimNotify_Begin_DoAction.h"
#include "Global.h"
#include "GlobalComponents/CWeaponComponent.h"
#include "GlobalComponents/CDoAction.h"

FString UCAnimNotify_Begin_DoAction::GetNotifyName_Implementation() const
{
	return "Begin_DoAction";
}

void UCAnimNotify_Begin_DoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	NullCheck(weapon);
	NullCheck(weapon->GetDoAction());

	weapon->GetDoAction()->Begin_DoAction();
}
