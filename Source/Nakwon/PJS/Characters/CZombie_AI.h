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
	UPROPERTY(VisibleDefaultsOnly)
	class UCZAIBehaviorComponent* Behavior;

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
	ACZombie_AI();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void Damaged() override;

public:
	void End_Damaged() override;

private:
	class ACharacter* Target;
};
