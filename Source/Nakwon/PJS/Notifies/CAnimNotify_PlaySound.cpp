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

	if (!!Source)
	{
		UGameplayStatics::PlaySoundAtLocation(actor->GetWorld(), Source, actor->GetActorLocation(), Volume, Pitch, Start, Attenuation);

		if (bNoise)
			MeshComp->GetOwner()->MakeNoise(Loudness, Cast<APawn>(actor), actor->GetActorLocation(), Range);
	}
}
