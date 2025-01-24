#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRandSetComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UCRandSetComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "CharacterAsset")
	class UCCharacterAsset* DataAsset;

public:	
	UCRandSetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
private:
	class ACharacter* Owner;

};
