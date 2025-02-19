#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Sleep.generated.h"

UCLASS()
class NAKWON_API UCBTTaskNode_Sleep : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_Sleep();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
