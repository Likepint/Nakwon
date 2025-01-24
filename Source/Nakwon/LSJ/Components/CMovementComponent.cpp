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

	Owner = Cast<ACharacter>(GetOwner());
}

void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	Owner->AddControllerYawInput(InVal.Get<FVector2D>().X * 0.5);

	// Vertical
	Owner->AddControllerPitchInput(InVal.Get<FVector2D>().Y * 0.5);
}
