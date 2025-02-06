#include "PJS/Weapons/CZDoAction.h"
#include "Global.h"
#include "PJS/Weapons/CZAttachment.h"
#include "PJS/Weapons/CZEquipment.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CZStateComponent.h"
#include "PJS/Components/CZMovementComponent.h"

UCZDoAction::UCZDoAction()
{

}

void UCZDoAction::BeginPlay(ACZAttachment * InAttachment, UCZEquipment * InEquipment, ACharacter * InOwner, const TArray<FZDoActionData>& InDoActionDatas, const TArray<FZHitData>& InHitDatas)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	State = CHelpers::GetComponent<UCZStateComponent>(OwnerCharacter);
	Movement = CHelpers::GetComponent<UCZMovementComponent>(OwnerCharacter);

	DoActionDatas = InDoActionDatas;
	HitDatas = InHitDatas;
}

void UCZDoAction::DoAction()
{
	bInAction = true;

	State->SetActionMode();
}

void UCZDoAction::Begin_DoAction()
{
	bBeginAction = true;
}

void UCZDoAction::End_DoAction()
{
	bInAction = false;
	bBeginAction = false;

	State->SetIdleMode();

	Movement->Move();
	Movement->DisableFixedCamera();
}
