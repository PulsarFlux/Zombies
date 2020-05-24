// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BTDec_CheckAngleToPlayerHeading.h"

UBTDec_CheckAngleToPlayerHeading::UBTDec_CheckAngleToPlayerHeading() :
	UBTDecorator()
{
	bNotifyTick = true;
}

bool UBTDec_CheckAngleToPlayerHeading::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) const
{
	FVector PlayerLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FVector PawnLoc = (OwnerComp.GetAIOwner())->GetPawn()->GetActorLocation();
	FVector PawnRelativeLoc = PawnLoc - PlayerLoc;
	FVector PlayerDir = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorRotation().Vector();
	float CosOfAngle = FVector::DotProduct(PlayerDir, PawnRelativeLoc) / (PlayerDir.Size() * PawnRelativeLoc.Size());

	if (CosOfAngle >= FMath::Cos(UKismetMathLibrary::GetPI() * AngleToCheck / 180.0f))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UBTDec_CheckAngleToPlayerHeading::TickNode(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool RawCond = CalculateRawConditionValue(OwnerComp, NodeMemory);
	if ((IsInversed() && RawCond) | (!IsInversed() && !RawCond))
	{
		OwnerComp.RequestExecution(this);
	}
}


