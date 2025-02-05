#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()

public:
	// 장착 애니메이션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	// 애니메이션의 속도
	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	// 이동할 수 있냐 없냐
	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	// 무기 장착 시 화면을 정면으로 고정할것이냐
	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;
};

UCLASS()
class NAKWON_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
	
};
