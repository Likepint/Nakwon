#include "GlobalComponents/CWeaponAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GlobalComponents/CWeaponData.h"
#include "GlobalComponents/CAttachment.h"

UCWeaponAsset::UCWeaponAsset()
{
	AttachmentClass = ACAttachment::StaticClass();

}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner, UCWeaponData** OutWeaponData)
{
	ACAttachment* attachment = nullptr;
	if (!!AttachmentClass) // AttachmentClass != nullptr
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, params);
	}

	*OutWeaponData = NewObject<UCWeaponData>();
	(*OutWeaponData)->Attachment = attachment;
}
