#include "PJS/Characters/CZAIController.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Components/CZAIBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACZAIController::ACZAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 300;
	Sight->LoseSightRadius = 400;
	Sight->PeripheralVisionAngleDegrees = 20;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACZAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACZAIController::OnPerceptionUpdated);
}

void ACZAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Zombie = Cast<ACZombie_AI>(InPawn);
	SetGenericTeamId(Zombie->GetTeamID());

	NullCheck(Zombie->GetBehaviorTree());

	UBlackboardComponent* blackboard = Blackboard.Get();
	if (UseBlackboard(Zombie->GetBehaviorTree()->BlackboardAsset, blackboard))
		this->Blackboard = blackboard;

	Behavior = CHelpers::GetComponent<UCZAIBehaviorComponent>(Zombie);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(Zombie->GetBehaviorTree());
}

void ACZAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACZAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor *> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	if (actors.Num() > 0)
	{
		Blackboard->SetValueAsObject("Target", actors[0]);

		return;
	}

	Blackboard->SetValueAsObject("Target", nullptr);
}