#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IZombie.generated.h"

UINTERFACE(MinimalAPI)
class UIZombie : public UInterface
{
	GENERATED_BODY()
};

class NAKWON_API IIZombie
{
	GENERATED_BODY()

public:
	virtual void End_Damaged() {}
	virtual void End_Dead() {}

};
