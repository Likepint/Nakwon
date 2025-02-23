#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CGameMode.generated.h"

UCLASS()
class NAKWON_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ACGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StaminaWidgetClass;

	UPROPERTY()
	UUserWidget* StaminaWidget;
};
