// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttemptIntercept.generated.h"

/**
 * Run towards predicted intercept with player character (based purely on current velocity) 
 */
UCLASS()
class ZOMBIES_API UBTTask_AttemptIntercept : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_AttemptIntercept();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	FVector FindIntercept(FVector PawnLoc, float PawnSpeed);
};
