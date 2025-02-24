#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Hand, Bat, Woodstick, Brick, MAX
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UCWeaponAsset* DataAssets[(int32)EWeaponType::MAX];

public:
	FORCEINLINE EWeaponType GetWeaponType() { return Type; }

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::MAX; }
	FORCEINLINE bool IsHandMode() { return Type == EWeaponType::Hand; }
	FORCEINLINE bool IsBatMode() { return Type == EWeaponType::Bat; }
	FORCEINLINE bool IsWoodstickMode() { return Type == EWeaponType::Woodstick; }
	FORCEINLINE bool IsBrickMode() { return Type == EWeaponType::Brick; }

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
private:
	bool IsIdleMode();

public:
	class ACAttachment* GetAttachment();
	class UCEquipment* GetEquipment();
	class UCDoAction* GetDoAction();

public:
	void SetUnarmedMode();
	void SetHandMode();
	void SetBatMode();
	void SetWoodstickMode();
	void SetBrickMode();

	UFUNCTION(BlueprintCallable)
	void DoAction();
	void SetIsAiming(const bool& bAiming);

private:
	void SetMode(EWeaponType InType);
	void ChangeType(EWeaponType InType);

public:
	FWeaponTypeChanged OnWeaponTypeChange;

private:
	class ACharacter* OwnerCharacter;

	EWeaponType Type = EWeaponType::MAX;

private:
	UPROPERTY()
	class UCWeaponData* Datas[(int32)EWeaponType::MAX];

};
