#include "PJS/Weapons/DoActions/CZDoAction_Combo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "PJS/Components/CZStateComponent.h"

void UCZDoAction_Combo::DoAction()
{
	TrueCheck(DoActionDatas.Num() < 1);

	if (bEnable)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	FalseCheck(State->IsIdleMode());

	Super::DoAction();
	DoActionDatas[Index].DoAction(OwnerCharacter);
}

void UCZDoAction_Combo::Begin_DoAction()
{
	Super::Begin_DoAction();
	FalseCheck(bExist);

	bExist = false;
	DoActionDatas[++Index].DoAction(OwnerCharacter);
}

void UCZDoAction_Combo::End_DoAction()
{
	Super::End_DoAction();

	Index = 0;
}

void UCZDoAction_Combo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOther);
	NullCheck(InOther);

	//CLog::Log(InOther->GetName());

	//FActionDamageEvent e;
	//e.HitData = &HitDatas[0];

	//InOther->TakeDamage(e.HitData->Power, e, InAttacker->GetController(), InAttackCauser);

	for (ACharacter* hitted : Hitted)
		TrueCheck(hitted == InOther);

	Hitted.AddUnique(InOther);

	TrueCheck(HitDatas.Num() - 1 < Index);
	HitDatas[Index].SendDamage(InAttacker, InAttackCauser, InOther);
}

void UCZDoAction_Combo::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	float angle = -2.0f;
	ACharacter* candidate = nullptr;

	for (ACharacter* hitted : Hitted)
	{
		FVector direction = hitted->GetActorLocation() - OwnerCharacter->GetActorLocation();
		direction = direction.GetSafeNormal2D();


		FVector forward = FQuat(OwnerCharacter->GetActorRotation()).GetForwardVector();

		float dot = FVector::DotProduct(direction, forward);
		if (dot >= angle)
		{
			angle = dot;
			candidate = hitted;
		}
	}

	if (!!candidate)
	{
		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), candidate->GetActorLocation());
		FRotator target = FRotator(0, rotator.Yaw, 0);

		AController* controller = OwnerCharacter->GetController<AController>();
		controller->SetControlRotation(target);
	}

	Hitted.Empty();
}
