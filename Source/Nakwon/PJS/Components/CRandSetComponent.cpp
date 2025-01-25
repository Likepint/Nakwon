#include "PJS/Components/CRandSetComponent.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CCharacterAsset.h"

UCRandSetComponent::UCRandSetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UCCharacterAsset> asset(L"/Script/Nakwon.CCharacterAsset'/Game/PJS/Characters/DA_CCharacterAsset.DA_CCharacterAsset'");
	if (asset.Succeeded())
		DataAsset = asset.Object;
}

void UCRandSetComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	if (!!Owner)
		DataAsset->BeginPlay(Owner);
}

void UCRandSetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
