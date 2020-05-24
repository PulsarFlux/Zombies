// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "Pickup.h"
#include "PickupSpawnVolume.h"

// Sets default values
APickupSpawnVolume::APickupSpawnVolume()
	: ASpawnVolume()
{

}

void APickupSpawnVolume::SetPickupTimeoutTime(float Time)
{
	PickupTimeoutTime = Time;
}

void APickupSpawnVolume::SpawnObject(TSubclassOf<AActor> WhatToSpawn)
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0;
			SpawnRotation.Pitch = 0;
			SpawnRotation.Roll = 0;

			TArray<AActor*> OverlappingActors;

			FVector SpawnLocation = FVector(0, 0, 0);
			//Generate spawn locations until only overlaps with the spawn volume
			bool Overlap = true;
			while (Overlap)
			{
				SpawnLocation = GetRandomPointInVolume();
				APickup* SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedPickup->GetOverlappingActors(OverlappingActors);
				//For allowable spawn should only overlap with the spawn volume itself, should be possible to check this only using number of overlaps
				if (OverlappingActors.Num() <= 1)
				{
					Overlap = false;
					SpawnedPickup->Spawned(PickupTimeoutTime);
				}
				else
				{
					SpawnedPickup->Destroy();
				}
			}
		}
	}
}
