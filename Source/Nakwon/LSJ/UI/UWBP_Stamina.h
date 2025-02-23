#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSJ/Components/CMovementComponent.h"
#include "UWBP_Stamina.generated.h"

UCLASS()
class NAKWON_API UUWBP_Stamina : public UUserWidget
{
	GENERATED_BODY()
	
 public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetMovementComponent(class UCMovementComponent* NewMovementComponent);

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetStaminaPercent() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UCMovementComponent* MovementComponent;
};
