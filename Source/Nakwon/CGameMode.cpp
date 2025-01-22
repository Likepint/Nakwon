#include "CGameMode.h"
#include "LSJ/CCharacter.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<ACharacter> asset(L"/Script/Engine.Blueprint'/Game/LSJ/BP_CCharacter.BP_CCharacter_C'");

	if (asset.Succeeded())
		DefaultPawnClass = asset.Class;
}
