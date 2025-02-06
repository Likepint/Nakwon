#include "PJS/Weapons/CZWeaponAsset.h"
#include "Global.h"
#include "PJS/Weapons/CZAttachment.h"
#include "PJS/Weapons/CZEquipment.h"
#include "PJS/Weapons/CZDoAction.h"
//#include "PJS/Weapons/CZSubAction.h"
#include "PJS/Weapons/CZWeaponData.h"
#include "GameFramework/Character.h"

UCZWeaponAsset::UCZWeaponAsset()
{
	AttachmentClass = ACZAttachment::StaticClass();
	EquipmentClass = UCZEquipment::StaticClass();	
}

void UCZWeaponAsset::BeginPlay(ACharacter * InOwner, UCZWeaponData** OutWeaponData)
{
	ACZAttachment* attachment = nullptr;
	if (!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACZAttachment>(AttachmentClass, params);
	}

	UCZEquipment* equipment = nullptr;
	if (!!EquipmentClass)
	{
		equipment = NewObject<UCZEquipment>(this, EquipmentClass);
		equipment->BeginPlay(InOwner, EquipmentData);

		if (!!attachment)
		{
			equipment->OnEquipmentBeginEquip.AddDynamic(attachment, &ACZAttachment::OnBeginEquip);
			equipment->OnEquipmentUnequip.AddDynamic(attachment, &ACZAttachment::OnUnequip);
		}
	}

	UCZDoAction* doAction = nullptr;
	if (!!DoActionClass)
	{
		doAction = NewObject<UCZDoAction>(this, DoActionClass);
		doAction->BeginPlay(attachment, equipment, InOwner, DoActionDatas, HitDatas);

		if (!!attachment)
		{
			attachment->OnAttachmentBeginCollision.AddDynamic(doAction, &UCZDoAction::OnAttachmentBeginCollision);
			attachment->OnAttachmentEndCollision.AddDynamic(doAction, &UCZDoAction::OnAttachmentEndCollision);

			attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &UCZDoAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(doAction, &UCZDoAction::OnAttachmentEndOverlap);
		}

		if (!!equipment)
		{
			equipment->OnEquipmentBeginEquip.AddDynamic(doAction, &UCZDoAction::OnBeginEquip);
			equipment->OnEquipmentUnequip.AddDynamic(doAction, &UCZDoAction::OnUnequip);
		}
	}

	//UCSubAction* subAction = nullptr;
	//if (!!SubActionClass)
	//{
	//	subAction = NewObject<UCSubAction>(this, SubActionClass);
	//	subAction->BeginPlay(InOwner, attachment, doAction);
	//}


	*OutWeaponData = NewObject<UCZWeaponData>();
	(*OutWeaponData)->Attachment = attachment;
	(*OutWeaponData)->Equipment = equipment;
	(*OutWeaponData)->DoAction = doAction;
	//(*OutWeaponData)->SubAction = subAction;
}

#if WITH_EDITOR
void UCZWeaponAsset::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	TrueCheck(FApp::IsGame());


	bool bRefresh = false;

	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("DoActionDatas") == 0;
	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0;

	if (bRefresh)
	{
		bool bCheck = false;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate;

		if (bCheck)
		{
			FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			TSharedPtr<IDetailsView> detailsView = prop.FindDetailView("WeaponAssetEditorDetailsView");

			if (detailsView.IsValid())
				detailsView->ForceRefresh();
		}
	}
}
#endif //WITH_EDITOR
