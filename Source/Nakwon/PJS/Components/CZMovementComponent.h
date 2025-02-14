#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CZMovementComponent.generated.h"

UENUM()
enum class EZSpeed : uint8
{
	Walk = 0, Run, MAX
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UCZMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
	float HorizontalLook = 45;

	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
	float VerticalLook = 45;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)EZSpeed::MAX] = { 50, 300 };

public:
	FORCEINLINE bool CanMove() { return bCanMove; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)EZSpeed::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)EZSpeed::Run]; }

	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

	FORCEINLINE void EnableTopViewCamera() { bTopViewCamera = true; }
	FORCEINLINE void DisableTopViewCamera() { bTopViewCamera = false; }

public:	
	UCZMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetSpeed(EZSpeed InType);

public:
	void OnWalk();
	void OnRun();

	void EnableControlRotation();
	void DisableControlRotation();

public:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

public:
	void Move();
	void Stop();

private:
	class ACharacter* OwnerCharacter;

private:
	bool bCanMove = true;
	bool bFixedCamera;
	bool bTopViewCamera;
};
