// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PJS/Weapons/CZWeaponStructures.h"
#include "CZWeaponAsset.generated.h"

UCLASS()
class NAKWON_API UCZWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACZAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	FZEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCZEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCZDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
	TArray<FZDoActionData> DoActionDatas;

	UPROPERTY(EditAnywhere)
	TArray<FZHitData> HitDatas;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class UCSubAction> SubActionClass;

public:
	UCZWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCZWeaponData** OutWeaponData);

#if WITH_EDITOR
	void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR
};
