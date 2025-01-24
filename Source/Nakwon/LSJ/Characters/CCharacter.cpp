#include "LSJ/Characters/CCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "LSJ/Components/CMovementComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	// 캐릭터 생성자에 IA랑 IMC 생성
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/LSJ/Inputs/IMC_Default.IMC_Default'"));
	if (IMC_DEFAULT.Succeeded()) {
		IMC_Default = IMC_DEFAULT.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVEMENT(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Movement.IA_Movement'"));
	if (IA_MOVEMENT.Succeeded()) {
		IA_Movement = IA_MOVEMENT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Look.IA_Look'"));
	if (IA_LOOK.Succeeded()) {
		IA_Look = IA_LOOK.Object;
	}

	// CMovementComponent로부터 컴포넌트 생성
	Movement = CreateDefaultSubobject<UCMovementComponent>("Movement");


}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, Movement, &UCMovementComponent::OnMovement);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, Movement, &UCMovementComponent::OnLook);
	}
}
