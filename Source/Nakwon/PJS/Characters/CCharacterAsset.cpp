#include "PJS/Characters/CCharacterAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CZombie.h"
#include "PJS/Characters/CAnimInstance_Zombie.h"
#include "Components/SkeletalMeshComponent.h"

UCCharacterAsset::UCCharacterAsset()
{

}

void UCCharacterAsset::BeginPlay(ACharacter* InOwner)
{
	if (ACZombie* character = Cast<ACZombie>(InOwner))
	{
		USkeletalMesh* mesh = SkeletalMesh[character->GetGender()];
		character->GetMesh()->SetSkeletalMesh(mesh);

		switch (character->GetGender())
		{
			case 0: // Man
			{
				character->GetMesh()->SetMaterial(0, Cloth_M[FMath::RandRange(0, Cloth_M.Num() - 1)]);
				character->GetMesh()->SetMaterial(1, UpperBody_M[FMath::RandRange(0, UpperBody_M.Num() - 1)]);
				character->GetMesh()->SetMaterial(2, LowerBody_M[FMath::RandRange(0, LowerBody_M.Num() - 1)]);

				break;
			}

			case 1: // Woman
			{
				character->GetMesh()->SetMaterial(0, LowerBody_W[FMath::RandRange(0, LowerBody_W.Num() - 1)]);
				character->GetMesh()->SetMaterial(1, UpperBody_W[FMath::RandRange(0, UpperBody_W.Num() - 1)]);
				character->GetMesh()->SetMaterial(2, Cloth_W[FMath::RandRange(0, Cloth_W.Num() - 1)]);

				break;
			}
		}
	}
}
