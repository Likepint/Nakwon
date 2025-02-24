#include "Components/CMontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCMontageComponent::UCMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "DataTable is not selected");

		return;
	}
	OwnerCharacter = Cast<ACharacter>(GetOwner());


	TArray<FMontagesData*> datas;
	DataTable->GetAllRows<FMontagesData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::MAX; i++)
	{
		for (FMontagesData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}//for(data)
	}//for(i)
}

void UCMontageComponent::PlayDeadMode()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCMontageComponent::PlayAnimMontage(EStateType InType)
{
	NullCheck(OwnerCharacter);

	FMontagesData* data = Datas[(int32)InType];

	if (data == nullptr || data->Montage == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "None montages data");

		return;
	}

	OwnerCharacter->PlayAnimMontage(data->Montage, data->PlayRate);
}
