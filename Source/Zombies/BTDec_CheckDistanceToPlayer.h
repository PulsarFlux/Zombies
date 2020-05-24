// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDec_CheckDistanceToPlayer.generated.h"

/**
 * Returns true if the distance between the player and the pawn is less than the value set in DistanceToCheck
 */
UCLASS()
class ZOMBIES_API UBTDec_CheckDistanceToPlayer : public UBTDecorator
{
	GENERATED_BODY()

		UBTDec_CheckDistanceToPlayer();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Distance")
	float DistanceToCheck;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
