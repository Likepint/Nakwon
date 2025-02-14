#include "PJS/Characters/CZombie_AI.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "PJS/Components/CZMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "PJS/Components/CZAIBehaviorComponent.h"
//#include "Components/WidgetComponent.h"
//#include "PJS/Components/CZStatusComponent.h"
//#include "Widgets/CUserWidget_Label.h"

ACZombie_AI::ACZombie_AI()
{
	State = CreateDefaultSubobject<UCStateComponent>("State");
	Movement = CreateDefaultSubobject<UCZMovementComponent>("Movement");
	Weapon = CreateDefaultSubobject<UCWeaponComponent>("Weapon");

	State->SetSleepMode();

	//CHelpers::CreateComponent<UWidgetComponent>(this, &LabelWidget, "Label", GetMesh());

	//CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");
	//CHelpers::CreateActorComponent<UCZAIBehaviorComponent>(this, &Behavior, "Behavior");

	//TSubclassOf<UCUserWidget_Label> labelClass;
	//CHelpers::GetClass<UCUserWidget_Label>(&labelClass, "WidgetBlueprint'/Game/Widgets/WB_Label.WB_Label_C'");
	//LabelWidget->SetWidgetClass(labelClass);
	//LabelWidget->SetRelativeLocation(FVector(0, 0, 220));
	//LabelWidget->SetDrawSize(FVector2D(120, 0));
	//LabelWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACZombie_AI::BeginPlay()
{
	Super::BeginPlay();

	Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ACZombie_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!State->IsSleepMode() and !!Target)
	{
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

		SetActorRotation(FQuat(rot));

		FVector direction = Target->GetActorLocation() - GetActorLocation();

		AddMovementInput(direction.GetSafeNormal());
	}
}

void ACZombie_AI::UpdateLabelRenderScale()
{

}

void ACZombie_AI::Hitted()
{
	Super::Hitted();

	//TrueCheck(State->IsDeadMode());

	Behavior->SetDamagedMode();
}

void ACZombie_AI::End_Damaged()
{
	Super::Hitted();

	Behavior->SetWaitMode();
}