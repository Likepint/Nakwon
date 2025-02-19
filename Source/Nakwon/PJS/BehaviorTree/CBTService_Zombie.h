#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Zombie.generated.h"

UCLASS()
class NAKWON_API UCBTService_Zombie : public UBTService
{
	GENERATED_BODY()
	
	private:
	UPROPERTY(EditAnywhere, Category = "Action")
		float ActionRange = 150;

public:
	UCBTService_Zombie();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
