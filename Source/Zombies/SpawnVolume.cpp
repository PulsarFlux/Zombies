// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpawnVolume.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

UBoxComponent* ASpawnVolume::GetSpawnBox()
{
	return SpawnBox;
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnBoxOrigin = SpawnBox->Bounds.Origin;
	FVector SpawnBoxExtent = SpawnBox->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnBoxOrigin, SpawnBoxExtent);
}

void ASpawnVolume::SpawnObject(TSubclassOf<AActor> WhatToSpawn)
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetRandomPointInVolume();

			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0;
			SpawnRotation.Pitch = 0;
			SpawnRotation.Roll = 0;

			World->SpawnActor<AActor>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}


