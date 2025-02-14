#include "PJS/Components/CZMovementComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCZMovementComponent::UCZMovementComponent()
{

}

void UCZMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCZMovementComponent::SetSpeed(EZSpeed InType)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}

void UCZMovementComponent::OnRun()
{
	SetSpeed(EZSpeed::Run);
}

void UCZMovementComponent::OnWalk()
{
	SetSpeed(EZSpeed::Walk);
}

void UCZMovementComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCZMovementComponent::DisableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UCZMovementComponent::OnMoveForward(float InAxis)
{
	FalseCheck(bCanMove);

	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	if (bTopViewCamera)
		direction = FVector::XAxisVector;

	OwnerCharacter->AddMovementInput(direction, InAxis);
}

void UCZMovementComponent::OnMoveRight(float InAxis)
{
	FalseCheck(bCanMove);

	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	if (bTopViewCamera)
		direction = FVector::YAxisVector;

	OwnerCharacter->AddMovementInput(direction, InAxis);
}

void UCZMovementComponent::OnHorizontalLook(float InAxis)
{
	TrueCheck(bFixedCamera);

	OwnerCharacter->AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void UCZMovementComponent::OnVerticalLook(float InAxis)
{
	TrueCheck(bFixedCamera);

	OwnerCharacter->AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

void UCZMovementComponent::Move()
{
	bCanMove = true;
}

void UCZMovementComponent::Stop()
{
	bCanMove = false;
}