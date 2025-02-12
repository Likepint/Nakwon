#include "CAnimInstance_Player.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "LSJ/Characters/CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance_Player::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


}

void UCAnimInstance_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if (ACharacter* character = Cast<ACharacter>(TryGetPawnOwner()))
	{
		Owner = Cast<ACCharacter>(character);
		NullCheck(Owner);
	}
}

void UCAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	NullCheck(Owner);

	Speed = Owner->GetVelocity().Size2D();
}
