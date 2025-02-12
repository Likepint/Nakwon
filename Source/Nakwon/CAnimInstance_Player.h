#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Player.generated.h"

UCLASS()
class NAKWON_API UCAnimInstance_Player : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAnim")
	float Speed;
	
public:
	virtual void NativeInitializeAnimation() override;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* Owner;

};
