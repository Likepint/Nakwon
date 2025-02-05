#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquipment.generated.h"

UCLASS()
class NAKWON_API UCEquipment : public UObject
{
	GENERATED_BODY()
	
private:
	//FEquipmentData Data;

private:
	class UCMovementComponent* Movement;

	class ACharacter* OwnerCharacter;

private:
	bool bBeginEquip;
	bool bEquipped;
};
