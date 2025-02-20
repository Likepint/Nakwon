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
#include "LSJ/Components/CMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CAttachment_Projectile.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0.0f, -90.0f, 0.0f))); // quaternion

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	CSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("CSpawnPoint"));
	CSpawnPoint->SetupAttachment(Camera);
	CSpawnPoint->SetRelativeLocation(FVector(274, 0, -2.5));
	CSpawnPoint->SetRelativeRotation(FRotator(180, 0, 0));

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
		IA_Bat = IA_BAT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ATTACK(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Attack.IA_Attack'"));
	if (IA_ATTACK.Succeeded()) {
		IA_Attack = IA_ATTACK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_PROJECTILE(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Projectile.IA_Projectile'"));
	if (IA_PROJECTILE.Succeeded()) {
		IA_Projectile = IA_PROJECTILE.Object;
	}

	// CStateComponent 생성
	State = CreateDefaultSubobject<UCStateComponent>("State");

	// CMovementComponent로부터 컴포넌트 생성
	Movement = CreateDefaultSubobject<UCMovementComponent>("Movement");

	// CWeaponComponent로부터 컴포넌트 생성
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

	Movement->DisableControlRotationd();

	Movement->SetSpeed(ESpeed::PlayerWalk);
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

		if (bCanShoot)
		{
			EnhancedInputComponent->BindAction(IA_Projectile, ETriggerEvent::Triggered, this, &ACCharacter::Draw);
			EnhancedInputComponent->BindAction(IA_Projectile, ETriggerEvent::Completed, this, &ACCharacter::Shoot);
		}
	}
}

void ACCharacter::Draw()
{
	bThrow = true;

	if (!bCanShoot) return;

	if (Weapon->GetAttachment())
		Weapon->SetIsAiming(true);

	Movement->Stop();
	Movement->EnableControlRotationd();

	FVector StartLocation = CSpawnPoint->GetComponentLocation();
	FVector FromDir = GetActorLocation();
	FVector ToDir = StartLocation;
	FVector LaunchDirection = UKismetMathLibrary::GetDirectionUnitVector(FromDir, ToDir);

	float Speed = 800.f;
	float Radius = 0.f;
	float MaxSimTime = 2.0f;
	float Frequency = 30.0f;

	FPredictProjectilePathParams PathParams;

	PathParams.StartLocation = StartLocation;
	PathParams.LaunchVelocity = LaunchDirection * Speed;
	PathParams.bTraceWithCollision = true;
	PathParams.ProjectileRadius = Radius;
	PathParams.MaxSimTime = MaxSimTime;
	PathParams.SimFrequency = Frequency;
	PathParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	PathParams.TraceChannel = ECC_Visibility;

	FPredictProjectilePathResult PathResult;

	if (UGameplayStatics::PredictProjectilePath(GetWorld(), PathParams, PathResult))
	{
		for (const FPredictProjectilePathPointData& PointData : PathResult.PathData)
		{
			DrawDebugSphere(GetWorld(), PointData.Location, 5.0f, 12, FColor::Red, false, 0.01);
		}
	}
}


void ACCharacter::Shoot()
{
	bThrow = false;

	if (!bCanShoot) return;
	bCanShoot = false;

	if (Weapon->GetAttachment())
		Weapon->SetIsAiming(false);

	FVector StartLocation = CSpawnPoint->GetComponentLocation();
	FVector FromDir = GetActorLocation();
	FVector ToDir = StartLocation;
	FVector LaunchDirection = UKismetMathLibrary::GetDirectionUnitVector(FromDir, ToDir);

	float Speed = 800.f;
	float Radius = 5.0f;
	float MaxSimTime = 2.0f;
	float Frequency = 30.0f;

	FPredictProjectilePathParams PathParams;

	PathParams.StartLocation = StartLocation;
	PathParams.LaunchVelocity = LaunchDirection * Speed;
	PathParams.bTraceWithCollision = true;
	PathParams.ProjectileRadius = Radius;
	PathParams.MaxSimTime = MaxSimTime;
	PathParams.SimFrequency = Frequency;
	PathParams.DrawDebugType = EDrawDebugTrace::None;
	PathParams.TraceChannel = ECC_Visibility;


	FPredictProjectilePathResult PathResult;

	if (UGameplayStatics::PredictProjectilePath(GetWorld(), PathParams, PathResult))
	{
		ACAttachment_Projectile* SpawnedProjectile = GetWorld()->SpawnActor<ACAttachment_Projectile>(Projectile, StartLocation, FRotator::ZeroRotator);

		if (SpawnedProjectile)
		{

			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(SpawnedProjectile->GetComponentByClass(UStaticMeshComponent::StaticClass()));

			if (MeshComponent) {

				MeshComponent->SetSimulatePhysics(true);
				MeshComponent->SetPhysicsLinearVelocity(LaunchDirection * Speed, false);

			}
		}
	}

	auto a = [this]()
		{
			bCanShoot = true;
		};

	GetWorld()->GetTimerManager().SetTimer(coolTimer, FTimerDelegate::CreateLambda(a), 3.f, true);
}

void ACCharacter::CoolTime()
{
	bCanShoot = true;
}
