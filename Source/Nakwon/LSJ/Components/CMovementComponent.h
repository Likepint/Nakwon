#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMovementComponent.generated.h"

UENUM()
enum class ESpeed : uint8
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	ZombieWalk = 0, ZombieRun, PlayerWalk, PlayerRun, MAX
=======
	Walk = 0, Run, MAX
>>>>>>> Stashed changes
=======
	Walk = 0, Run, MAX
>>>>>>> Stashed changes
};

UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class NAKWON_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
	float HorizontalLook = 45;

	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
	float VerticalLook = 45;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)ESpeed::MAX] = { 200, 300, 250, 400 };

public:
	FORCEINLINE bool CanMove() { return bCanMove; }

	FORCEINLINE float GetZombieWalkSpeed() { return Speed[(int32)ESpeed::ZombieWalk]; }
	FORCEINLINE float GetZombieRunSpeed() { return Speed[(int32)ESpeed::ZombieRun]; }
	FORCEINLINE float GetPlayerWalkSpeed() { return Speed[(int32)ESpeed::PlayerWalk]; }
	FORCEINLINE float GetPlayerRunSpeed() { return Speed[(int32)ESpeed::PlayerRun]; }
=======
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)ESpeed::MAX] = { 200, 400 };
>>>>>>> Stashed changes

=======
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)ESpeed::MAX] = { 200, 400 };

>>>>>>> Stashed changes
public:
	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

<<<<<<< Updated upstream
<<<<<<< Updated upstream
	FORCEINLINE void EnableTopViewCamera() { bTopViewCamera = true; }
	FORCEINLINE void DisableTopViewCamera() { bTopViewCamera = false; }

=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
public:	
	UCMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetSpeed(ESpeed InType);
<<<<<<< Updated upstream
<<<<<<< Updated upstream

=======
=======
>>>>>>> Stashed changes
		
>>>>>>> Stashed changes
public:
	void OnMovement(const struct FInputActionValue& InVal);
	void OnLook(const struct FInputActionValue& InVal);

	void OnRun(const struct FInputActionValue& InVal);
	void OffRun(const struct FInputActionValue& InVal);

	void EnableControlRotation();
	void DisableControlRotation();

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