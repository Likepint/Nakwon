#include "PJS/Components/CZAIBehaviorComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UCZAIBehaviorComponent::UCZAIBehaviorComponent()
{

}

void UCZAIBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

}

ACharacter* UCZAIBehaviorComponent::GetTarget()
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(TargetKey));
}

FVector UCZAIBehaviorComponent::GetPatrolLocation()
{
	return Blackboard->GetValueAsVector(PatrolLocationKey);
}

void UCZAIBehaviorComponent::SetPatrolLocation(const FVector& InLocation)
{
	Blackboard->SetValueAsVector(PatrolLocationKey, InLocation);
}

EAIStateType UCZAIBehaviorComponent::GetType()
{
	return (EAIStateType)Blackboard->GetValueAsEnum(AIStateTypeKey);
}

bool UCZAIBehaviorComponent::IsSleepMode()
{
	return false;
}

bool UCZAIBehaviorComponent::IsWaitMode()
{
	return GetType() == EAIStateType::Wait;
}

bool UCZAIBehaviorComponent::IsApproachMode()
{
	return GetType() == EAIStateType::Approach;
}

bool UCZAIBehaviorComponent::IsActionMode()
{
	return GetType() == EAIStateType::Action;
}

bool UCZAIBehaviorComponent::IsPatrolMode()
{
	return GetType() == EAIStateType::Patrol;
}

bool UCZAIBehaviorComponent::IsDamagedMode()
{
	return GetType() == EAIStateType::Damaged;
}

bool UCZAIBehaviorComponent::IsDeadMode()
{
	return GetType() == EAIStateType::Dead;
}

void UCZAIBehaviorComponent::SetSleepMode()
{
	//ChangeType(EAIStateType::Sleep);
}

void UCZAIBehaviorComponent::SetWaitMode()
{
	ChangeType(EAIStateType::Wait);
}

void UCZAIBehaviorComponent::SetApproachMode()
{
	ChangeType(EAIStateType::Approach);
}

void UCZAIBehaviorComponent::SetActionMode()
{
	ChangeType(EAIStateType::Action);
}

void UCZAIBehaviorComponent::SetPatrolMode()
{
	ChangeType(EAIStateType::Patrol);
}

void UCZAIBehaviorComponent::SetDamagedMode()
{
	ChangeType(EAIStateType::Damaged);
}

void UCZAIBehaviorComponent::SetDeadMode()
{
	ChangeType(EAIStateType::Dead);
}

void UCZAIBehaviorComponent::ChangeType(EAIStateType InType)
{
	EAIStateType prevType = GetType();

	Blackboard->SetValueAsEnum(AIStateTypeKey, (uint8)InType);

	if (OnAIStateTypeChanged.IsBound())
		OnAIStateTypeChanged.Broadcast(prevType, InType);
}
