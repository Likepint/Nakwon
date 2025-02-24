#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"

USTRUCT()
struct FMontagesData
	: public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* DataTable;

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayDeadMode();

private:
	void PlayAnimMontage(EStateType InType);

private:
	class ACharacter* OwnerCharacter;
	FMontagesData* Datas[(int32)EStateType::MAX];
};

