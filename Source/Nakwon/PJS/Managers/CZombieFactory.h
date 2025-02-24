#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CZombieFactory.generated.h"

UCLASS()
class NAKWON_API ACZombieFactory : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Count")
	int32 ZombieCount = 0;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* SpawnExtent;

protected:
	UPROPERTY(EditAnywhere, Category = "Zombies")
	TSubclassOf<class ACZombie> ZombieFactory;
	
public:	
	ACZombieFactory();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void MakeZombie();

};
