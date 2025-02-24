#include "PJS/BehaviorTree/CBTService_Zombie.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CZAIController.h"
#include "PJS/Characters/CZombie_AI.h"
#include "Components/CStateComponent.h"
#include "PJS/Components/CZAIBehaviorComponent.h"

UCBTService_Zombie::UCBTService_Zombie()
{
	NodeName = "Melee";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Zombie::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ACZombie_AI* ai = Cast<ACZombie_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCZAIBehaviorComponent* aiState = CHelpers::GetComponent<UCZAIBehaviorComponent>(ai);


	if (state->IsDamagedMode())
	{
		aiState->SetDamagedMode();

		return;
	}


	ACharacter* target = aiState->GetTarget();
	if (target == nullptr)
	{
		aiState->SetPatrolMode();

		return;
	}

	float distance = ai->GetDistanceTo(target);
	if (distance < ActionRange)
	{
		aiState->SetActionMode();

		return;
	}

	if (!state->IsActionMode())
		aiState->SetApproachMode();
}
