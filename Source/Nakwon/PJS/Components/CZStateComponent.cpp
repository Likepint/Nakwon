#include "PJS/Components/CZStateComponent.h"

UCZStateComponent::UCZStateComponent()
{

}

void UCZStateComponent::BeginPlay()
{
	Super::BeginPlay();

}
void UCZStateComponent::SetIdleMode()
{
	ChangeType(EState::Idle);
}

void UCZStateComponent::SetEquipMode()
{
	ChangeType(EState::Equip);
}

void UCZStateComponent::SetActionMode()
{
	ChangeType(EState::Action);
}

void UCZStateComponent::SetHittedMode()
{
	ChangeType(EState::Hitted);
}

void UCZStateComponent::SetDeadMode()
{
	ChangeType(EState::Dead);
}

void UCZStateComponent::SetSleepMode()
{
	ChangeType(EState::Sleep);
}

void UCZStateComponent::ChangeType(EState InType)
{
	EState prevType = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, Type);
}

void UCZStateComponent::OnSubActionMode()
{
	bInSubActionMode = true;
}

void UCZStateComponent::OffSubActionMode()
{
	bInSubActionMode = false;
}