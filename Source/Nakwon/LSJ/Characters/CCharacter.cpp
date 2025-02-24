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
#include "PJS/Characters/CZombie.h"
#include "Animation/AnimMontage.h"
#include "Components/CStatusComponent.h"
#include "Weapons/CWeaponStructures.h"

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
	Camera->SetRelativeLocation(FVector(90, 50, 0));

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	CSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("CSpawnPoint"));
	CSpawnPoint->SetupAttachment(Camera);
	CSpawnPoint->SetRelativeLocation(FVector(180, -40, 30));
	CSpawnPoint->SetRelativeRotation(FRotator(0, 0, 0));
	//CSpawnPoint->SetCollisionProfileName(FName("CSpawnPoint"));
	//CSpawnPoint->OnComponentBeginOverlap.AddDynamic(this, &ACCharacter::OnCSpawnOverlap);
	
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

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_CROUCH(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Crouch.IA_Crouch'"));
	if (IA_CROUCH.Succeeded()) {
		IA_Crouch = IA_CROUCH.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_CHOKE(TEXT("/Script/EnhancedInput.InputAction'/Game/LSJ/Inputs/IA_Choke.IA_Choke'"));
	if (IA_CHOKE.Succeeded()) {
		IA_Choke = IA_CHOKE.Object;
	}


	// CStateComponent 생성
	State = CreateDefaultSubobject<UCStateComponent>("State");

	// CMovementComponent로부터 컴포넌트 생성
	Movement = CreateDefaultSubobject<UCMovementComponent>("Movement");

	// CStatus로부터 컴포넌트 생성
	Status = CreateDefaultSubobject<UCStatusComponent>("Status");

	// CWeaponComponent로부터 컴포넌트 생성
	Weapon = CreateDefaultSubobject<UCWeaponComponent>("Weapon");


	ConstructorHelpers::FObjectFinder<UAnimMontage> ChokeAnim(TEXT("/Script/Engine.AnimMontage'/Game/LSJ/Animations/Choke.Choke'"));
	if (ChokeAnim.Succeeded())
	{
		ChokeAnimationMontage = ChokeAnim.Object;
	}

}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 스태미나 위젯 생성 및 추가
	if (StaminaWidgetClass)
	{
		StaminaWidget = CreateWidget<UUserWidget>(GetWorld(), StaminaWidgetClass);
		if (StaminaWidget)
		{
			StaminaWidget->AddToViewport();
		}
	}


	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}

	Movement->DisableControlRotationd();

	Movement->SetSpeed(ESpeed::PlayerWalk);

	State->OnStateTypeChanged.AddDynamic(this, &ACCharacter::OnStateTypeChanged);
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

		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, Movement, &UCMovementComponent::OnCrouch);
		
		
		EnhancedInputComponent->BindAction(IA_Choke, ETriggerEvent::Started, this, &ACCharacter::OnChoke);



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

	FVector ToLeft = GetActorRightVector() * -0.f;
	LaunchDirection.Z *= 0.8f;
	LaunchDirection = (LaunchDirection + ToLeft).GetSafeNormal();

	float Speed = 700.f;
	float Radius = 5.f;
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

	FVector ToLeft = GetActorRightVector() * -0.f;
	LaunchDirection.Z *= 0.8f;
	LaunchDirection = (LaunchDirection + ToLeft).GetSafeNormal();

	float Speed = 700.f;
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
			USphereComponent* MeshComponent = Cast<USphereComponent>(SpawnedProjectile->GetComponentByClass(USphereComponent::StaticClass()));

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

float ACCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Power = damage;
	Damage.Character = Cast<ACharacter>(EventInstigator->GetPawn());
	Damage.Causer = DamageCauser;
	Damage.Event = (FActionDamageEvent*)&DamageEvent;

	State->SetDamagedMode();

	return damage;
}

void ACCharacter::Damaged()
{
	//Apply Damage
	{
		Status->Damage(Damage.Power);
		Damage.Power = 0;
	}

	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		data->PlayMontage(this);
		data->PlayHitStop(GetWorld());
		data->PlaySoundWave(this);
		data->PlayEffect(GetWorld(), GetActorLocation(), GetActorRotation());

		if (Status->IsDead() == false)
		{
			FVector start = GetActorLocation();
			FVector target = Damage.Character->GetActorLocation();
			FVector direction = target - start;
			direction.Normalize();

			LaunchCharacter(-direction * data->Launch, false, false);
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
		}
	}

	if (Status->IsDead())
	{
		State->SetDeadMode();

		return;
	}

	Damage.Character = nullptr;
	Damage.Causer = nullptr;
	Damage.Event = nullptr;
}

void ACCharacter::End_Damaged()
{
	State->SetIdleMode();
}

void ACCharacter::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Montage->PlayDeadMode();
}

void ACCharacter::End_Dead()
{

}

void ACCharacter::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Damaged: Damaged(); break;
	case EStateType::Dead: Dead(); break;
	}
}

void ACCharacter::OnChoke(const FInputActionValue& InVal)
{
	if (GetMesh() && ChokeAnimationMontage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(ChokeAnimationMontage))
		{
			AnimInstance->Montage_Play(ChokeAnimationMontage);
			GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Choke!"));
		}
	}
}

void ACCharacter::OnZombieAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACZombie* zombie = Cast<ACZombie>(OtherActor);
	if (zombie) {

	}
}
