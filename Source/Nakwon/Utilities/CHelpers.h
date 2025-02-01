#pragma once

#include "CoreMinimal.h"

#define TRUE true
#define FALSE false

#define TrueCheck(X) { if (X == TRUE) return; }
#define TrueCheckResult(X, Y) { if (X == TRUE) return Y; }

#define FalseCheck(X) { if (X == FALSE) return; }
#define FalseCheckResult(X, Y) { if (X == FALSE) return Y; }

#define NullCheck(X) { if (X == nullptr) return; }
#define NullCheckResult(X, Y) { if (X == nullptr) return Y; }

class NAKWON_API CHelpers
{
public:
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		*OutClass = asset.Class;
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}
};
