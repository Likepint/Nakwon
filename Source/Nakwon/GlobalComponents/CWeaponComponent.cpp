#include "GlobalComponents/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GlobalComponents/CWeaponAsset.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	NullCheck(Owner);

	for (int32 i = 0; i < (int32)EWeaponType::MAX; ++i)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(Owner, &Datas[i]);
	}
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
