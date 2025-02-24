#include "PJS/BehaviorTree/CBTTaskNode_Sleep.h"
#include "Global.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Characters//CZAIController.h"
#include "Components/CStateComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PJS/Components/CZAIBehaviorComponent.h"

UCBTTaskNode_Sleep::UCBTTaskNode_Sleep()
{
	NodeName = "Sleep";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Sleep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());

	controller->StopMovement();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Sleep::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ACZombie_AI* ai = Cast<ACZombie_AI>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCZAIBehaviorComponent* behavior = CHelpers::GetComponent<UCZAIBehaviorComponent>(ai);

	if (state->IsSleepMode() == false or behavior->GetTarget() != nullptr)
	{
		state->SetIdleMode();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}
