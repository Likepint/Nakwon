#include "CharacterDebuggerCategory.h"
#include "CanvasItem.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "LSJ/CCharacter.h"

CharacterDebuggerCategory::CharacterDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;

}

CharacterDebuggerCategory::~CharacterDebuggerCategory()
{
	
}

TSharedRef<class FGameplayDebuggerCategory> CharacterDebuggerCategory::MakeInstance()
{
	return MakeShareable(new CharacterDebuggerCategory());
}

void CharacterDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	ACCharacter* player = OwnerPC->GetPawn<ACCharacter>();
	if (player == nullptr) return;

	// Player Character Datas
	{
		PlayerPawnData.bDraw = true;

		PlayerPawnData.ActorLocation = player->GetActorLocation();
		PlayerPawnData.Velocity = player->GetVelocity().Size2D();
		PlayerPawnData.Direction = FVector2D(player->GetActorForwardVector().X, player->GetActorRightVector().Y);
	}
}

void CharacterDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.5f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::White, L"Location : %s", *PlayerPawnData.ActorLocation.ToString());
	CanvasContext.Printf(FColor::White, L"Velocity : %f", PlayerPawnData.Velocity);
	CanvasContext.Printf(FColor::White, L"Direction : %s", *PlayerPawnData.Direction.ToString());
}
