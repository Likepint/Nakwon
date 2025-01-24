#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMovementComponent.generated.h"

UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class NAKWON_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMovementComponent();

public:
	void OnMovement(const struct FInputActionValue& InVal);
	void OnLook(const struct FInputActionValue& InVal);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
private:
	class ACharacter* Owner;
};