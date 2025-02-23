#include "LSJ/Components/CMovementComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "LSJ/Characters/CCharacter.h"

UCMovementComponent::UCMovementComponent()
{
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	StaminaDecreaseRate = 10.0f;
	StaminaRecoveryRate = 5.0f;
	bIsRunning = false;
}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	bCrouched = false;

	// 스태미나 관리용 타이머 시작
	GetWorld()->GetTimerManager().SetTimer(StaminaTimerHandle, this, &UCMovementComponent::UpdateStamina, 0.1f, true);
}

void UCMovementComponent::SetSpeed(ESpeed InType)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}

void UCMovementComponent::OnMovement(const FInputActionValue& InVal)
{
	FalseCheck(bCanMove);

	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	//rotator에는 전방방향 구하는 함수가 없어서 Quat으로 변경함

	// Forward
	OwnerCharacter->AddMovementInput(FQuat(rotator).GetForwardVector(), InVal.Get<FVector2D>().X);

	// Right
	OwnerCharacter->AddMovementInput(FQuat(rotator).GetRightVector(), InVal.Get<FVector2D>().Y);
}

void UCMovementComponent::OnLook(const FInputActionValue& InVal)
{
	// Horizontal
	OwnerCharacter->AddControllerYawInput(InVal.Get<FVector2D>().X * .5);
	// Vertical
	OwnerCharacter->AddControllerPitchInput(InVal.Get<FVector2D>().Y * 0.5);
}

void UCMovementComponent::OnRun(const FInputActionValue& InVal)
{
	if (Stamina > 0.0f)
	{
		bIsRunning = true;
		SetSpeed(ESpeed::PlayerRun);
	}
}

void UCMovementComponent::OffRun(const FInputActionValue& InVal)
{
	bIsRunning = false;
	SetSpeed(ESpeed::PlayerWalk);
}

void UCMovementComponent::OnCrouch(const FInputActionValue& InVal)
{
	auto player = Cast<ACCharacter>(OwnerCharacter);
	NullCheck(OwnerCharacter);

	if (player->bCrouched) {
		OwnerCharacter->GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = false;
		OwnerCharacter->UnCrouch();
		player->bCrouched = false;
	}
	else {
		OwnerCharacter->GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
		OwnerCharacter->Crouch();
		player->bCrouched = true;
	}
}

void UCMovementComponent::EnableControlRotationd()
{
	NullCheck(OwnerCharacter);

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCMovementComponent::DisableControlRotationd()
{
	NullCheck(OwnerCharacter);

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}
void UCMovementComponent::Move()
{
	bCanMove = true;
}

void UCMovementComponent::Stop()
{
	bCanMove = false;
}

void UCMovementComponent::UpdateStamina()
{
	if (bIsRunning) 
	{
		Stamina -= 0.1f;
		Stamina = FMath::Clamp(Stamina, 0.f, 100.f);
	}

	if (Stamina == 0.f)
	{
		bIsRunning = false;
		SetSpeed(ESpeed::PlayerWalk);
	}
}

float UCMovementComponent::GetStamina() const
{
	return Stamina;

}
