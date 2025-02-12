#include "LSJ/Notifies/CAnimNotify_End_DoAction.h"
#include "Global.h"
#include "GlobalComponents/CWeaponComponent.h"
#include "GlobalComponents/CDoAction.h"

FString UCAnimNotify_End_DoAction::GetNotifyName() const
{
	return "End_DoAction";
}

void UCAnimNotify_End_DoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	NullCheck(weapon);
	NullCheck(weapon->GetDoAction());

	weapon->GetDoAction()->End_DoAction();
}
