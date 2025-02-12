#include "PJS/Characters/CAnimInstance_Zombie.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CZombie.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance_Zombie::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	DefaultIDX = FMath::RandRange(0, 3);
	WalkIDX = FMath::RandRange(0, 3);
	RunIDX = FMath::RandRange(0, 3);
}

void UCAnimInstance_Zombie::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if(ACharacter* character = Cast<ACharacter>(TryGetPawnOwner()))
	{
		Owner = Cast<ACZombie>(character);
		NullCheck(Owner);
	}
	
}

void UCAnimInstance_Zombie::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	NullCheck(Owner);

	Speed = Owner->GetVelocity().Size2D();

}
