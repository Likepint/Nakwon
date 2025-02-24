#include "PJS/BehaviorTree/CBTTaskNode_Action.h"
#include "Global.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Characters/CZAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ai = Cast<ACZombie_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	NullCheckResult(weapon, EBTNodeResult::Failed);

	controller->StopMovement();
	weapon->DoAction();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!!ai)
	{
		UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
		UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);

		bool bCheck = true;
		bCheck &= (state->IsIdleMode());
		bCheck &= (weapon->GetDoAction()->GetInAction() == false);

		if (bCheck)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

			return;
		}
	}
}

EBTNodeResult::Type UCBTTaskNode_Action::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	if (!!ai)
	{
		if (UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai))
		{
			bool bBeginAction = weapon->GetDoAction()->GetBeginAction();
			if (bBeginAction == false)
				weapon->GetDoAction()->Begin_DoAction();

			weapon->GetDoAction()->End_DoAction();

			return EBTNodeResult::Succeeded;
		}
		else return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
