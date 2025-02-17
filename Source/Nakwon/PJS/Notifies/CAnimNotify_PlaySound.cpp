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

	if (!!Sound.source)
	{
		UGameplayStatics::PlaySoundAtLocation(actor->GetWorld(), Sound.source, actor->GetActorLocation(), Sound.Volume, Sound.Pitch, Sound.Start, Sound.Attenuation);

		if (Noise.bNoise)
			MeshComp->GetOwner()->MakeNoise(Noise.Loudness, Cast<APawn>(actor), actor->GetActorLocation(), Noise.Range);
	}
}
