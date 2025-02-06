#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CZWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeapon : uint8
{
	Fist, Sword, Hammer, Warp, Around, Bow, MAX,
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponChanged, EWeapon, InPrevType, EWeapon, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UCZWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UCZWeaponAsset* DataAssets[(int32)EWeapon::MAX];

public:
	FORCEINLINE EWeapon GetWeaponType() { return Type; }

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeapon::MAX; }
	FORCEINLINE bool IsFistMode() { return Type == EWeapon::Fist; }
	FORCEINLINE bool IsSwordMode() { return Type == EWeapon::Sword; }
	FORCEINLINE bool IsHammerMode() { return Type == EWeapon::Hammer; }
	FORCEINLINE bool IsWarpMode() { return Type == EWeapon::Warp; }
	FORCEINLINE bool IsAroundMode() { return Type == EWeapon::Around; }
	FORCEINLINE bool IsBowMode() { return Type == EWeapon::Bow; }

public:	
	UCZWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
private:
	bool IsIdleMode();

public:
	class ACZAttachment* GetAttachment();
	class UCZEquipment* GetEquipment();
	class UCZDoAction* GetDoAction();

//public:
//	UFUNCTION(BlueprintCallable)
//	class UCSubAction* GetSubAction();

public:
	void SetUnarmedMode();
	void SetFistMode();
	void SetSwordMode();
	void SetHammerMode();
	void SetWarpMode();
	void SetAroundMode();
	void SetBowMode();

	void DoAction();

//public:
//	UFUNCTION(BlueprintCallable)
//	void SubAction_Pressed();
//
//	UFUNCTION(BlueprintCallable)
//	void SubAction_Released();

private:
	void SetMode(EWeapon InType);
	void ChangeType(EWeapon InType);

public:
	FWeaponChanged OnWeaponChange;

private:
	class ACharacter* OwnerCharacter;

	EWeapon Type = EWeapon::MAX;

private:
	UPROPERTY()
	class UCZWeaponData* Datas[(int32)EWeapon::MAX];
};
