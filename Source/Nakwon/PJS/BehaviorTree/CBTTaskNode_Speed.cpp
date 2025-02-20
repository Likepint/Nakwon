#include "PJS/BehaviorTree/CBTTaskNode_Speed.h"
#include "Global.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Characters/CZAIController.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ACZombie_AI* ai = Cast<ACZombie_AI>(controller->GetPawn());
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(ai);

	movement->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}
