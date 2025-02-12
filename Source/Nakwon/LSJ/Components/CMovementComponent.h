#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMovementComponent.generated.h"

UENUM()
enum class ECSpeed : uint8
{
	Walk = 0, Run, MAX
};

UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class NAKWON_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCMovementComponent();
private:
	UPROPERTY(EditAnywhere, Category = CameraSpeed)
	float HorizontalLook = 45;

	UPROPERTY(EditAnywhere, Category = CameraSpeed)
	float VerticalLook = 45;

private:
	UPROPERTY(EditAnywhere, Category = Speed)
	float Speed[(int32)ECSpeed::MAX] = { 50,150 };

public:
	FORCEINLINE bool CanMove() { return bCanMove; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ECSpeed::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ECSpeed::Run]; }

	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

	FORCEINLINE void EnableTopViewCamera() { bTopViewCamera = true; }
	FORCEINLINE void DisableTopViewCamera() { bTopViewCamera = false; }

protected:
	virtual void BeginPlay() override;

public:
	void SetSpeed(ECSpeed InType);

public:
	void OnMovement(const struct FInputActionValue& InVal);
	void OnLook(const struct FInputActionValue& InVal);

	void OnRun(const struct FInputActionValue& InVal);
	void OffRun(const struct FInputActionValue& InVal);

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
	class ACharacter* Owner;

private:
	bool bCanMove = true;
	bool bFixedCamera;
	bool bTopViewCamera;
};