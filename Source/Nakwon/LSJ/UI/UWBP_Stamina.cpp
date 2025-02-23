#include "LSJ/UI/UWBP_Stamina.h"
#include "../Components/CMovementComponent.h"


float UUWBP_Stamina::GetStaminaPercent() const
{
    if (MovementComponent)
    {
        return MovementComponent->GetStamina() / MovementComponent->GetMaxStamina();
    }
    return 1.0f;
}

void UUWBP_Stamina::SetMovementComponent(class UCMovementComponent* NewMovementComponent)
{
	MovementComponent = NewMovementComponent;
}
