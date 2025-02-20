#include "Notifies/CAnimNotify_End_State.h"
#include "Global.h"
#include "PJS/Characters/IZombie.h"

FString UCAnimNotify_End_State::GetNotifyName_Implementation() const
{
	return "End_State";
}

void UCAnimNotify_End_State::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	IIZombie* character = Cast<IIZombie>(MeshComp->GetOwner());
	NullCheck(character);

	switch (StateType)
	{
	case EStateType::Dead: character->End_Dead(); break;
	case EStateType::Damaged: character->End_Damaged(); break;
	}
}