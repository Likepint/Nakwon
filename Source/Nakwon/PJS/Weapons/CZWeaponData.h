#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CZWeaponData.generated.h"

UCLASS()
class NAKWON_API UCZWeaponData : public UObject
{
	GENERATED_BODY()
	
private:
	friend class UCZWeaponAsset;

public:
	FORCEINLINE class ACZAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UCZEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCZDoAction* GetDoAction() { return DoAction; }
	//FORCEINLINE class UCZSubAction* GetSubAction() { return SubAction; }

private:
	UPROPERTY()
	class ACZAttachment* Attachment;

	UPROPERTY()
	class UCZEquipment* Equipment;

	UPROPERTY()
	class UCZDoAction* DoAction;

	//UPROPERTY()
	//class UCSubAction* SubAction;

};
