#include "PJS/Characters/CZombie_AI.h"
#include "Global.h"
//#include "PJS/Components/CZWeaponComponent.h"
#include "PJS/Components/CZAIBehaviorComponent.h"
//#include "Components/WidgetComponent.h"
//#include "PJS/Components/CZStatusComponent.h"
//#include "Widgets/CUserWidget_Label.h"

ACZombie_AI::ACZombie_AI()
{
	//CHelpers::CreateComponent<UWidgetComponent>(this, &LabelWidget, "Label", GetMesh());

	//CHelpers::CreateActorComponent<UCZWeaponComponent>(this, &Weapon, "Weapon");
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

}

void ACZombie_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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