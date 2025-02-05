#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GlobalComponents/CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class NAKWON_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;
	
public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);

};