#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CCharacterAsset.generated.h"

UCLASS()
class NAKWON_API UCCharacterAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class USkeletalMesh*> SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class UMaterialInstance*> UpperBody_M;

	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class UMaterialInstance*> Cloth_M;

	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class UMaterialInstance*> LowerBody_M;

	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class UMaterialInstance*> UpperBody_W;

	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class UMaterialInstance*> Cloth_W;

	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	TArray<class UMaterialInstance*> LowerBody_W;

public:
	UCCharacterAsset();

	void BeginPlay(class ACharacter* InOwner);
};
