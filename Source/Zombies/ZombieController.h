// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "ZombieController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_API AZombieController : public AAIController
{
	GENERATED_BODY()
	
public:
	AZombieController();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
