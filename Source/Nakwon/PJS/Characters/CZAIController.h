#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CZAIController.generated.h"

UCLASS()
class NAKWON_API ACZAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* Perception;

public:
	ACZAIController();

protected:
	virtual void BeginPlay() override;

protected:
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private:
	class ACZombie_AI* Zombie;
	class UCZAIBehaviorComponent* Behavior;

	UPROPERTY(VisibleInstanceOnly)
	class UAISenseConfig_Hearing* Hearing;

	UPROPERTY(VisibleInstanceOnly)
	class UAISenseConfig_Sight* Sight;
};
