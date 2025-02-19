#include "PJS/Characters/CZombie_AI.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "LSJ/Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "PJS/Components/CZAIBehaviorComponent.h"

ACZombie_AI::ACZombie_AI()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UCZAIBehaviorComponent>(this, &Behavior, "Behavior");
}

void ACZombie_AI::BeginPlay()
{
	Super::BeginPlay();

	Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ACZombie_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACZombie_AI::Damaged()
{
	Super::Damaged();

	TrueCheck(State->IsDeadMode());

	//Behavior->SetDamagedMode();
}

void ACZombie_AI::End_Damaged()
{
	Super::End_Damaged();

	//Behavior->SetWaitMode();
}