#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GlobalComponents/CWeaponStructures.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "../PJS/Weapons/CZWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class NAKWON_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
	TArray<FDoActionData> DoActionDatas;

	UPROPERTY(EditAnywhere)
	TArray<FHitData> HitDatas;

public:
	FORCEINLINE class ACAttachment* GetAttachment() {
		return Attachment;
	}
	
	FORCEINLINE class UCEquipment* GetEquipment() {
		return Equipment;
	}

private:
	UPROPERTY()
	class ACAttachment* Attachment;
	
	UPROPERTY()
	class UCEquipment* Equipment;

public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);

};