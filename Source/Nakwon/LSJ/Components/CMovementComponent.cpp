#include "LSJ/Components/CMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"

UCMovementComponent::UCMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}

void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCMovementComponent::OnMovement(const FInputActionValue& InVal)
{
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
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void UCMovementComponent::OffRun(const FInputActionValue& InVal)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}

void UCMovementComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCMovementComponent::DisableControlRotation()
{
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
