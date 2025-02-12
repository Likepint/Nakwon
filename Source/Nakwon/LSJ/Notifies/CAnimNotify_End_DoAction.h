#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_End_DoAction.generated.h"

UCLASS()
class NAKWON_API UCAnimNotify_End_DoAction : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
