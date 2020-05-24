// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDec_CheckAngleToPlayerHeading.generated.h"

/**
 * Returns true if the actor lies in the triangle with half angular width AngleToCheck from the direction the player is heading
 */
UCLASS()
class ZOMBIES_API UBTDec_CheckAngleToPlayerHeading : public UBTDecorator
{
	GENERATED_BODY()
	UBTDec_CheckAngleToPlayerHeading();

public:
	//Angle in degrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle")
	float AngleToCheck;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
