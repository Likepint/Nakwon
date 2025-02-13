#pragma once

#include "CoreMinimal.h"
#include "PJS/Characters/CZombie.h"
#include "CZombie_AI.generated.h"

UCLASS()
class NAKWON_API ACZombie_AI : public ACZombie
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	uint8 TeamID = 2;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Label")
	float LabelViewAmount = 3000.0f;

//private:
//	UPROPERTY(EditAnywhere, Category = "Patrol")
//	class ACPatrolPath* PatrolPath;

//#if WITH_EDITOR
//private:
//	UPROPERTY(VisibleDefaultsOnly)
//	class UWidgetComponent* LabelWidget;
//#endif

//private:
//	UPROPERTY(VisibleDefaultsOnly)
//	class UCZWeaponComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
	class UCZAIBehaviorComponent* Behavior;

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

	//FORCEINLINE class ACPatrolPath* GetPatrolPath() { return PatrolPath; }

public:
	ACZombie_AI();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateLabelRenderScale();

protected:
	void Hitted() override;

public:
	void End_Damaged() override;
};
