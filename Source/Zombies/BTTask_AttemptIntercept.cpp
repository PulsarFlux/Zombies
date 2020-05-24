// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "AIController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BTTask_AttemptIntercept.h"

UBTTask_AttemptIntercept::UBTTask_AttemptIntercept() :
	UBTTaskNode()
{

}

EBTNodeResult::Type UBTTask_AttemptIntercept::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ACharacter* ZombieChar = Cast<ACharacter>((OwnerComp.GetAIOwner())->GetPawn());
	if (ZombieChar)
	{
		FVector PawnLoc = ZombieChar->GetActorLocation();
		FVector Destination = FindIntercept(PawnLoc, ZombieChar->GetCharacterMovement()->MaxWalkSpeed);
		FNavLocation Dummy;
		UNavigationSystem* NavSys = GetWorld()->GetNavigationSystem();
		if (NavSys->ProjectPointToNavigation(Destination, Dummy))
		{
			NavSys->SimpleMoveToLocation((OwnerComp.GetAIOwner()), Destination);
			//(OwnerComp.GetAIOwner())->MoveToLocation(Destination);
		}
		else
		{
			NavSys->SimpleMoveToActor((OwnerComp.GetAIOwner()), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		}
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

FVector UBTTask_AttemptIntercept::FindIntercept(FVector PawnLoc, float PawnSpeed)
{
	FVector PlayerLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FVector PawnRelativeLoc = PawnLoc - PlayerLoc;
	PawnRelativeLoc.Z = 0;
	FVector PlayerVel = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetVelocity();
	//Solve quadratic equation
	float A = PlayerVel.SizeSquared() - PawnSpeed * PawnSpeed;
	float B = -2 * FVector::DotProduct(PawnRelativeLoc, PlayerVel);
	float C = PawnRelativeLoc.SizeSquared();
	float RootDeterminant = FMath::Sqrt(B * B - 4 * A * C);
	//The two (plus and minus) solutions of the quadratic equation
	float MinusSol = (-1 * B - RootDeterminant)  / (2 * A);
	float PlusSol = (-1 * B + RootDeterminant) / (2 * A);
	if (MinusSol >= 0)
	{
		return PlayerLoc + MinusSol * PlayerVel;
	}
	else
	{
		return PlayerLoc + PlusSol * PlayerVel;
	}
}

