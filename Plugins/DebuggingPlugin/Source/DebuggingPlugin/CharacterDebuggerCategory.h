#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class DEBUGGINGPLUGIN_API CharacterDebuggerCategory
	: public FGameplayDebuggerCategory
{
public:
	CharacterDebuggerCategory();
	~CharacterDebuggerCategory();

public:
	static TSharedRef<class FGameplayDebuggerCategory> MakeInstance();

public:
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	struct FCategoryData
	{
		bool bDraw = false;
		FString Name;
		FVector ActorLocation;
		FVector ForwardVector;
		float Velocity;
		FVector2D Direction;
		FString State;
	};

private:
	FCategoryData PlayerPawnData;
};
