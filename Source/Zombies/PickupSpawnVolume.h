// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnVolume.h"
#include "PickupSpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_API APickupSpawnVolume : public ASpawnVolume
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APickupSpawnVolume();

	virtual void SpawnObject(TSubclassOf<AActor> WhatToSpawn) override;

	void SetPickupTimeoutTime(float Time);

protected:
	float PickupTimeoutTime;
};
