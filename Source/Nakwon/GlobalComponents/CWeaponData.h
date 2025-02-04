#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponData.generated.h"

UCLASS()
class NAKWON_API UCWeaponData : public UObject
{
	GENERATED_BODY()

private:
	friend class UCWeaponAsset;

public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	
private:
	UPROPERTY()
	class ACAttachment* Attachment;
};
