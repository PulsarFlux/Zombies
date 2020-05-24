// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "ZombieCharacter.h"
#include "ZombieSpawnVolume.h"
#include "BlockSpawnVolume.h"
#include "PickupSpawnVolume.h"
#include "PlayerCharacter.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "ZombiesGameMode.h"

AZombiesGameMode::AZombiesGameMode()
{

}

void AZombiesGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieSpawnVolume::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		AZombieSpawnVolume* SpawnVolumeActor = Cast<AZombieSpawnVolume>(Actor);
		ZombieSpawnVolumes.AddUnique(SpawnVolumeActor);
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlockSpawnVolume::StaticClass(), FoundActors);
	BlockSpawnVolume = Cast<ABlockSpawnVolume>(FoundActors[0]);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickupSpawnVolume::StaticClass(), FoundActors);
	PickupSpawnVolume = Cast<APickupSpawnVolume>(FoundActors[0]);
	PickupSpawnVolume->SetPickupTimeoutTime(BlockSpawnInterval);

	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetDestroyableBlockType(Block);

	SpawnCountdown = (float)BlockSpawnInterval;
	PickupTracker = 0;

	GetWorldTimerManager().SetTimer(ZombieSpawnTimer, this, &AZombiesGameMode::SpawnZombie, ZombieSpawnInterval, false);
	//GetWorldTimerManager().SetTimer(BlockSpawnTimer, this, &AZombiesGameMode::SpawnBlockAndPickup, BlockSpawnInterval, false);
	GetWorldTimerManager().SetTimer(CountdownTimer, this, &AZombiesGameMode::TickCountdown, 0.1f, false);

	if (PlayWidgetClass != nullptr && PauseWidgetClass != nullptr)
	{
		PlayWidget = CreateWidget<UUserWidget>(GetWorld(), PlayWidgetClass);
		if (PlayWidget != nullptr)
		{
			PlayWidget->AddToViewport();
		}
	}
}

void AZombiesGameMode::RestartTheGame()
{
	RestartGame();
}

void AZombiesGameMode::GameOver()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	if (PauseWidget != nullptr && PlayWidget != nullptr)
	{
		PauseWidget->AddToViewport();
		PlayWidget->RemoveFromViewport();
	}
}

float AZombiesGameMode::GetSpawnCountdown()
{
	return SpawnCountdown;
}

void AZombiesGameMode::TickCountdown()
{
	SpawnCountdown -= 0.1f;
	if (SpawnCountdown <= 0)
	{
		SpawnCountdown = (float)BlockSpawnInterval;
		AZombiesGameMode::SpawnBlockAndPickup();
	}
	GetWorldTimerManager().SetTimer(CountdownTimer, this, &AZombiesGameMode::TickCountdown, 0.1f, false);
}

void AZombiesGameMode::SpawnZombie()
{
	if (ZombieSpawnVolumes.Num() > 0)
	{
		int32 index = FMath::Rand() % ZombieSpawnVolumes.Num();
		ZombieSpawnVolumes[index]->SpawnObject(BaseZombie);
		GetWorldTimerManager().SetTimer(ZombieSpawnTimer, this, &AZombiesGameMode::SpawnZombie, ZombieSpawnInterval, false);
	}
}

void AZombiesGameMode::SpawnBlockAndPickup()
{
	if (BlockSpawnVolume != nullptr)
	{
		BlockSpawnVolume->SpawnObject(Block);
		RespawnZombiesInsideBlocks();
		if (PickupTracker == 3)
		{
			PickupTracker = 0;
			PickupSpawnVolume->SpawnObject(SpecialPickup);
		}
		else
		{
			PickupTracker += 1;
			PickupSpawnVolume->SpawnObject(BasePickup);
		}
	}
}

void AZombiesGameMode::RespawnZombiesInsideBlocks()
{
	TArray<AActor*> FoundBlocks;
	TArray<AActor*> TrappedZombies;

	int32 TotalNumTrappedZombies = 0;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Block, FoundBlocks);
	for (AActor* FoundBlock : FoundBlocks)
	{
		FoundBlock->GetOverlappingActors(TrappedZombies, AZombieCharacter::StaticClass());
		for (AActor* TrappedZombie : TrappedZombies)
		{
			TrappedZombie->Destroy();
			TotalNumTrappedZombies += 1;
		}
	}
	for (int32 i = 0; i < TotalNumTrappedZombies; i++)
	{
		SpawnZombie();
	}
}
