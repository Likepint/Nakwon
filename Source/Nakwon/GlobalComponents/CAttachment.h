#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "CAttachment.generated.h"

// Event 처리해야되는 다른 Class 들을 가져오기 위해 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCAttachmentBeginCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCAttachmentEndCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCAttachmentBeginOverlap, class ACharacter*, InAttacker, AActor*, InAttackCuaser, class ACharacter*, InOther);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCAttachmentEndOverlap, class ACharacter*, InAttacker, class ACharacter*, InOther);

UCLASS()
class NAKWON_API ACAttachment : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* Root;
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnBeginEquip();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequip();

protected:
	UFUNCTION(BlueprintCallable, Category="Attach")
	void AttachTo(FName InSocketName);

public:
	void OnCollisions();
	void OffCollisions();

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FCAttachmentBeginCollision OnAttachmentBeginCollision;
	FCAttachmentEndCollision OnAttachmentEndCollision;

	FCAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FCAttachmentEndOverlap OnAttachmentEndOverlap;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	TArray<class UShapeComponent*> Collisions;

};
