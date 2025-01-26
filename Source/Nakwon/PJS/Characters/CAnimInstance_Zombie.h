#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Zombie.generated.h"

UCLASS()
class NAKWON_API UCAnimInstance_Zombie : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	int32 DefaultIDX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	int32 WalkIDX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	int32 RunIDX;

public:
	virtual void NativeInitializeAnimation() override;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACZombie* Owner;

};
