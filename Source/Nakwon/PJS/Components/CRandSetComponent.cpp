#include "PJS/Components/CRandSetComponent.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CCharacterAsset.h"

UCRandSetComponent::UCRandSetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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
