#include "PJS/Characters/CCharacterAsset.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UCCharacterAsset::UCCharacterAsset()
{

}

void UCCharacterAsset::BeginPlay(ACharacter* InOwner)
{
	int32 gender = FMath::RandRange(0, 1);

	USkeletalMesh* mesh = SkeletalMesh[gender];
	InOwner->GetMesh()->SetSkeletalMesh(mesh);

	switch (gender)
	{
		case 0: // Man
		{
			InOwner->GetMesh()->SetMaterial(0, Cloth_M[FMath::RandRange(0, 7)]);
			InOwner->GetMesh()->SetMaterial(1, UpperBody_M[FMath::RandRange(0, 7)]);
			InOwner->GetMesh()->SetMaterial(2, LowerBody_M[FMath::RandRange(0, 9)]);

			break;
		}

		case 1: // Woman
		{
			InOwner->GetMesh()->SetMaterial(0, LowerBody_W[FMath::RandRange(0, 7)]);
			InOwner->GetMesh()->SetMaterial(1, UpperBody_W[FMath::RandRange(0, 7)]);
			InOwner->GetMesh()->SetMaterial(2, Cloth_W[FMath::RandRange(0, 7)]);

			break;
		}
	}
}
