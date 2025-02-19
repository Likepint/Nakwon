#include "PJS/BehaviorTree/CBTTaskNode_Damaged.h"
#include "Global.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Characters/CZAIController.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Damaged::UCBTTaskNode_Damaged()
{
	bNotifyTick = true;

	NodeName = "Damaged";
}

EBTNodeResult::Type UCBTTaskNode_Damaged::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());

	controller->StopMovement();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Damaged::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ACZombie_AI* ai = Cast<ACZombie_AI>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsDamagedMode() == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}
