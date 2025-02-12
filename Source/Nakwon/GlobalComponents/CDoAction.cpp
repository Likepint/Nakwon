#include "GlobalComponents/CDoAction.h"
#include "Global.h"
#include "GlobalComponents/CAttachment.h"
#include "GlobalComponents/CEquipment.h"
#include "GameFramework/Character.h"
#include "GlobalComponents/CStateComponent.h"
#include "LSJ/Components/CMovementComponent.h"

UCDoAction::UCDoAction()
{

}

void UCDoAction::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner, const TArray<FDoActionData>& InDoActionData, const TArray<FHitData>& InHitData)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	Movement = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	DoActionDatas = InDoActionData;
	HitDatas = InHitData;
}

void UCDoAction::DoAction()
{
	bInAction = true;

	State->SetActionMode();
}

void UCDoAction::Begin_DoAction()
{
	bBeginAction = true;
}

void UCDoAction::End_DoAction()
{
	bBeginAction = false;

	State->SetIdleMode();
	
	Movement->Move();
	Movement->DisableFixedCamera();
}