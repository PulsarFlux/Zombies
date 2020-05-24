// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnVolume.h"
#include "BlockSpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_API ABlockSpawnVolume : public ASpawnVolume
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABlockSpawnVolume();

	virtual void SpawnObject(TSubclassOf<AActor> WhatToSpawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 SpawnGroupWidth;
	
	//Check to see if Block to check overlaps with any of the objects in ExistingBlocks, and if it does destroy it.
	void HandleBlockBlockOverlap(AActor* BlockToCheck, TArray<AActor*> ExistingBlocks);
};
