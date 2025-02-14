#include "PJS/Characters/CAnimInstance_Zombie.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Characters/CZombie.h"
#include "Components/CStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance_Zombie::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UCAnimInstance_Zombie::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if(ACharacter* character = Cast<ACharacter>(TryGetPawnOwner()))
	{
		Owner = Cast<ACZombie>(character);
		NullCheck(Owner);

		Index  = Owner->GetIndex();
	}
}

void UCAnimInstance_Zombie::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	NullCheck(Owner);

	Speed = Owner->GetVelocity().Size2D();
	
	bSleep = CHelpers::GetComponent<UCStateComponent>(Owner)->IsSleepMode();
}
