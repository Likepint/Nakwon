#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class ECWeapon : uint8
{
	WoodStick = 0, Bat, Brick, MAX
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FECWeaponChanged, ECWeapon, InPrevType, ECWeapon, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NAKWON_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = DataAsset)
	class UCWeaponAsset* DataAssets[(int32)ECWeapon::MAX];

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECWeapon GetWeaponType() { return Type; }

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == ECWeapon::MAX; }
	FORCEINLINE bool IsWoodStickode() { return Type == ECWeapon::WoodStick; }
	FORCEINLINE bool IsBatMode() { return Type == ECWeapon::Bat; }
	FORCEINLINE bool IsBrickMode() { return Type == ECWeapon::Brick; }

public:
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float Deltatime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool IsIdleMode();

public:
	class ACAttachment* GetAttachment();
	class UCEquipment* GetEquipment();
	class UCDoAction* GetDoAction();

public:
	void SetUnarmedMode();
	void SetWoodStickMode();
	void SetBatMode();
	void SetBrickMode();

	void DoAction();

private:
	void SetMode(ECWeapon InType);
	void ChangeType(ECWeapon InType);

public:
	FECWeaponChanged OnCWeaponChange;

private:
	class ACCharacter* OwnerCharacter;

	ECWeapon Type = ECWeapon::MAX;

private:
	UPROPERTY()
	class UCWeaponData* Datas[(int32)ECWeapon::MAX];

};
