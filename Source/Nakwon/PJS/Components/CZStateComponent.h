#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CZStateComponent.generated.h"

UENUM()
enum class EState : uint8
{
	Idle = 0, Equip, Action, Hitted, Dead, Sleep, MAX
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EState, InPrevType, EState, InNewType);

UCLASS()
class NAKWON_API UCZStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsIdleMode() { return Type == EState::Idle; }
	FORCEINLINE bool IsEquipMode() { return Type == EState::Equip; }
	FORCEINLINE bool IsActionMode() { return Type == EState::Action; }
	FORCEINLINE bool IsHittedMode() { return Type == EState::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EState::Dead; }
	FORCEINLINE bool IsSleep() { return Type == EState::Sleep; }

	FORCEINLINE bool IsSubActionMode() { return bInSubActionMode; }

public:	
	UCZStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetIdleMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetSleepMode();

	void OnSubActionMode();
	void OffSubActionMode();

private:
	void ChangeType(EState InType);

public:
	FStateTypeChanged OnStateTypeChanged;

private:
	EState Type;

private:
	bool bInSubActionMode;
};
