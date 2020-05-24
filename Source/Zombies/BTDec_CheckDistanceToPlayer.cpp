// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "AIController.h"
#include "BTDec_CheckDistanceToPlayer.h"


UBTDec_CheckDistanceToPlayer::UBTDec_CheckDistanceToPlayer() :
	UBTDecorator()
{
	bNotifyTick = true;
}

bool UBTDec_CheckDistanceToPlayer::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) const
{
	//(OwnerComp.GetCurrentTree())-BlackboardAsset
	FVector PlayerLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FVector PawnLoc = (OwnerComp.GetAIOwner())->GetPawn()->GetActorLocation();
	//I have found some strange issues with using inbuilt distance functions
	float Dist = FMath::Sqrt((PlayerLoc.X - PawnLoc.X) * (PlayerLoc.X - PawnLoc.X) + (PlayerLoc.Y - PawnLoc.Y) * (PlayerLoc.Y - PawnLoc.Y) + (PlayerLoc.Z - PawnLoc.Z) * (PlayerLoc.Z - PawnLoc.Z));
	if (Dist <= DistanceToCheck)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UBTDec_CheckDistanceToPlayer::TickNode(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool RawCond = CalculateRawConditionValue(OwnerComp, NodeMemory);
	if ((IsInversed() && RawCond) | (!IsInversed() && !RawCond))
	{
		OwnerComp.RequestExecution(this);
	}
}