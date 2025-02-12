#include "LSJ/Characters/CCharacter.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LSJ/Components/CMovementComponent.h"
#include "GlobalComponents/CStateComponent.h"
#include "GlobalComponents/CWeaponComponent.h"


ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// GetCharacterMovement()->MaxWalkSpeed

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0.0f, -90.0f, 0.0f))); // quaternion

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

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_RUN(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Run.IA_Run'"));
	if (IA_RUN.Succeeded()) {
		IA_Run = IA_RUN.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_BAT(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Bat.IA_Bat'"));
	if (IA_BAT.Succeeded()) {
		IA_Bat= IA_BAT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ATTACK(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Attack.IA_Attack'"));
	if (IA_ATTACK.Succeeded()) {
		IA_Attack = IA_ATTACK.Object;
	}

	// CMovementComponent
	Movement = CreateDefaultSubobject<UCMovementComponent>("Movement");

	// CStateComponent
	State = CreateDefaultSubobject<UCStateComponent>("State");

	// CWeaponComponent
	Weapon = CreateDefaultSubobject<UCWeaponComponent>("Weapon");
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

		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Triggered, Movement, &UCMovementComponent::OnRun);
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, Movement, &UCMovementComponent::OffRun);

		EnhancedInputComponent->BindAction(IA_Bat, ETriggerEvent::Started, Weapon, &UCWeaponComponent::SetBatMode);

		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, Weapon, &UCWeaponComponent::DoAction);
	}
};