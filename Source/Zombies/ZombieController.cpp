// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "ZombieController.h"

AZombieController::AZombieController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.0f;
}

void AZombieController::Tick(float deltatime)
{
	Super::Tick(deltatime);

	if (GetMoveStatus() != EPathFollowingStatus::Moving)
	{
		MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}
}

// Called when the game starts or when spawned
void AZombieController::BeginPlay()
{
	Super::BeginPlay();

	MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
