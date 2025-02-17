#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_PlaySound.generated.h"

USTRUCT()
struct FSound
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class USoundWave* source;

	UPROPERTY(EditAnywhere)
	float Volume = 1;

	UPROPERTY(EditAnywhere)
	float Pitch = 1.f;
	
	UPROPERTY(EditAnywhere)
	float Start = 0.f;

	UPROPERTY(EditAnywhere)
	class USoundAttenuation* Attenuation;
};

USTRUCT()
struct FNoise
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bNoise = false;

	UPROPERTY(EditAnywhere)
	float Loudness = 1;

	UPROPERTY(EditAnywhere)
	float Range = 100;
};


UCLASS()
class NAKWON_API UCAnimNotify_PlaySound : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FSound Sound;

	UPROPERTY(EditAnywhere)
	FNoise Noise;
	
public:
	FString GetNotifyName() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
