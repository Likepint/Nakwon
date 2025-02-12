#include "LSJ/Components/CMovementComponent.h"
#include "Global.h"
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

	Owner = Cast<ACharacter>(GetOwner());

	Owner->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}

void UCMovementComponent::SetSpeed(ECSpeed InType)
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}

void UCMovementComponent::EnableControlRotation()
{
	Owner->bUseControllerRotationYaw = true;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCMovementComponent::DisableControlRotation()
{
	Owner->bUseControllerRotationYaw = false;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UCMovementComponent::OnMoveForward(float InAxis)
{
	FalseCheck(bCanMove);

	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	if (bTopViewCamera)
		direction = FVector::XAxisVector;

	Owner->AddMovementInput(direction, InAxis);
}

void UCMovementComponent::OnMoveRight(float InAxis)
{
	FalseCheck(bCanMove);

	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	if (bTopViewCamera)
		direction = FVector::YAxisVector;

	Owner->AddMovementInput(direction, InAxis);
}

void UCMovementComponent::OnHorizontalLook(float InAxis)
{
	TrueCheck(bFixedCamera);

	Owner->AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void UCMovementComponent::OnVerticalLook(float InAxis)
{
	TrueCheck(bFixedCamera);

	Owner->AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

void UCMovementComponent::Move()
{
	bCanMove = true;
}

void UCMovementComponent::Stop()
{
	bCanMove = false;
}

void UCMovementComponent::OnMovement(const FInputActionValue& InVal)
{
	// Forward
	Owner->AddMovementInput(Owner->GetActorForwardVector(), InVal.Get<FVector2D>().X);

	// Right
	Owner->AddMovementInput(Owner->GetActorRightVector(), InVal.Get<FVector2D>().Y);
}

void UCMovementComponent::OnLook(const FInputActionValue& InVal)
{
	// Horizontal
	Owner->AddControllerYawInput(InVal.Get<FVector2D>().X * .5);
	// Vertical
	Owner->AddControllerPitchInput(InVal.Get<FVector2D>().Y * 0.5);
}

void UCMovementComponent::OnRun(const FInputActionValue& InVal)
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void UCMovementComponent::OffRun(const FInputActionValue& InVal)
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}