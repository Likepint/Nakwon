#include "CGameMode.h"
#include "LSJ/Characters/CCharacter.h"
#include "Kismet/GameplayStatics.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<ACharacter> asset(L"/Script/Engine.Blueprint'/Game/LSJ/BP_CCharacter.BP_CCharacter_C'");

	if (asset.Succeeded())
		DefaultPawnClass = asset.Class;


	ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LSJ/WBP_Stamina.WBP_Stamina_C'"));
	if (WidgetAsset.Succeeded())
	{
		StaminaWidgetClass = WidgetAsset.Class;
	}
}

void ACGameMode::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (StaminaWidgetClass && PlayerCharacter)
	{
		StaminaWidget = CreateWidget<UUserWidget>(GetWorld(), StaminaWidgetClass);
		if (StaminaWidget)
		{
			StaminaWidget->AddToViewport();
		}
	}
}