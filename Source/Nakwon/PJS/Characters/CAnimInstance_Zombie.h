#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Zombie.generated.h"

UCLASS()
class NAKWON_API UCAnimInstance_Zombie : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float Speed;

public:
	virtual void NativeInitializeAnimation() override;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACZombie* Owner;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State")
	int32 Index;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State")
	bool bSleep = true;

};
