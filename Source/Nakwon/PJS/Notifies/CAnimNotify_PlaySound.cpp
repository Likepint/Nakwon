#include "PJS/Notifies/CAnimNotify_PlaySound.h"
#include "Global.h"

FString UCAnimNotify_PlaySound::GetNotifyName() const
{
	return "PlaySound";
}

void UCAnimNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	NullCheck(MeshComp);
	NullCheck(MeshComp->GetOwner());

	AActor* actor = MeshComp->GetOwner();

	if (!!Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(actor->GetWorld(), Sound, actor->GetActorLocation(), SoundScale);

		MeshComp->GetOwner()->MakeNoise(3, Cast<APawn>(actor), actor->GetActorLocation(), 100);
	}
}
