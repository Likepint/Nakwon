#include "PJS/Characters/CZAIController.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PJS/Characters/CZombie_AI.h"
#include "PJS/Components/CZAIBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/CStateComponent.h"

ACZAIController::ACZAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");

	// Perception_Hearing
	Perception_Hearing = CreateDefaultSubobject<UAIPerceptionComponent>("Perception_Hearing");

	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing");
	Hearing->HearingRange = 800;
	Hearing->bUseLoSHearing = true;
	Hearing->LoSHearingRange = 1000;
	Hearing	->SetMaxAge(2);

	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;

	Perception_Hearing->ConfigureSense(*Hearing);
	Perception_Hearing->SetDominantSense(*Hearing->GetSenseImplementation());

	// Perception_Sight
	Perception_Sight = CreateDefaultSubobject<UAIPerceptionComponent>("Perception_Sight");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 300;
	Sight->LoseSightRadius = 400;
	Sight->PeripheralVisionAngleDegrees = 20;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	Perception_Sight->ConfigureSense(*Sight);
	Perception_Sight->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACZAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception_Hearing->OnPerceptionUpdated.AddDynamic(this, &ACZAIController::OnPerceptionUpdated);
	Perception_Sight->OnPerceptionUpdated.AddDynamic(this, &ACZAIController::OnPerceptionUpdated);
}

void ACZAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CHelpers::GetComponent<UCStateComponent>(Zombie)->IsSleepMode())
		Perception_Sight->SetActive(false);
	else Perception_Sight->SetActive(true);
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
	Perception_Hearing->GetCurrentlyPerceivedActors(Hearing->StaticClass(), actors);

	if (Perception_Sight->IsActive())
		Perception_Sight->GetCurrentlyPerceivedActors(Hearing->StaticClass(), actors);

	if (actors.Num() > 0)
	{
		Blackboard->SetValueAsObject("Target", actors[0]);

		return;
	}

	Blackboard->SetValueAsObject("Target", nullptr);

	//for (const auto& actor : actors)
	//{
	//	FActorPerceptionBlueprintInfo info;
	//	Perception->GetActorsPerception(actor, info);

	//	if(info.LastSensedStimuli[0]. )

	//	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, actor->GetName());
	//}

	//Blackboard->SetValueAsObject("Target", actors[0]);

	//if (actors.Num() > 0)
	//{
	//	Blackboard->SetValueAsObject("Target", actors[0]);

	//	return;
	//}

	//Blackboard->SetValueAsObject("Target", nullptr);
}