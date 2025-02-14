#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_PlaySound.generated.h"

UCLASS()
class NAKWON_API UCAnimNotify_PlaySound : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
	class USoundWave* Sound;

	UPROPERTY(EditAnywhere)
	float SoundScale = 1;
};
