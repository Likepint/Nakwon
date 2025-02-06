#pragma once

#include "CoreMinimal.h"
#include "PJS/Weapons/CZDoAction.h"
#include "CZDoAction_Combo.generated.h"

UCLASS()
class NAKWON_API UCZDoAction_Combo : public UCZDoAction
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	void DoAction() override;
	void Begin_DoAction() override;
	void End_DoAction() override;

public:
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) override;
	void OnAttachmentEndCollision() override;

private:
	int32 Index;

	bool bEnable;
	bool bExist;

private:
	TArray<class ACharacter*> Hitted;

};
