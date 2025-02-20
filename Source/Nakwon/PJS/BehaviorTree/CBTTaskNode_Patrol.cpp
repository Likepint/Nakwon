#include "PJS/BehaviorTree/CBTTaskNode_Patrol.h"
#include "Global.h"
#include "CPatrolPath.h"
#include "Components/SplineComponent.h"
#include "PJS/Components/CZAIBehaviorComponent.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Characters/CZAIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ACZombie_AI* ai = Cast<ACZombie_AI>(controller->GetPawn());
	UCZAIBehaviorComponent* behavior = CHelpers::GetComponent<UCZAIBehaviorComponent>(ai);

	if (!!ai->GetPatrolPath())
	{
		FVector moveToPoint = ai->GetPatrolPath()->GetMoveTo();
		behavior->SetPatrolLocation(moveToPoint);

		if (bDebugMode)
			DrawDebugSphere(ai->GetWorld(), moveToPoint, 10, 10, FColor::Green, true, 5);

		return EBTNodeResult::InProgress;
	}


	FVector location = ai->GetActorLocation();

	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(ai->GetWorld());
	NullCheckResult(navSystem, EBTNodeResult::Failed);

	FNavLocation point(location);
	while (true)
	{
		if (navSystem->GetRandomPointInNavigableRadius(location, RandomRadius, point))
			break;
	}

	behavior->SetPatrolLocation(point.Location);

	if (bDebugMode)
		DrawDebugSphere(ai->GetWorld(), point.Location, 10, 10, FColor::Green, true, 5);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACZAIController* controller = Cast<ACZAIController>(OwnerComp.GetOwner());
	ACZombie_AI* ai = Cast<ACZombie_AI>(controller->GetPawn());
	UCZAIBehaviorComponent* behavior = CHelpers::GetComponent<UCZAIBehaviorComponent>(ai);


	FVector location = behavior->GetPatrolLocation();
	EPathFollowingRequestResult::Type result = controller->MoveToLocation(location, AcceptanceDistance, false);

	switch (result)
	{
	case EPathFollowingRequestResult::Failed:
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	break;

	case EPathFollowingRequestResult::AlreadyAtGoal:
	{
		if (ai->GetPatrolPath())
			ai->GetPatrolPath()->UpdateIndex();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	break;
	}
}
