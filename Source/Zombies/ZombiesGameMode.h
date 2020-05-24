// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ZombiesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_API AZombiesGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AZombiesGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Spawning")
	float GetSpawnCountdown();

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void RestartTheGame();

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GameOver();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float ZombieSpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 BlockSpawnInterval;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnZombie();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnBlockAndPickup();

	void TickCountdown();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> BaseZombie;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> Block;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> BasePickup;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> SpecialPickup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> PlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> PauseWidgetClass;

	UUserWidget* PlayWidget;
	UUserWidget* PauseWidget;
	
private:
	//delete and respawn all the zombies that had blocks spawned on top of them
	void RespawnZombiesInsideBlocks();

	TArray<class AZombieSpawnVolume*> ZombieSpawnVolumes;

	class ABlockSpawnVolume* BlockSpawnVolume;

	class APickupSpawnVolume* PickupSpawnVolume;
	
	FTimerHandle ZombieSpawnTimer;

	FTimerHandle CountdownTimer;

	FTimerHandle BlockSpawnTimer;

	float SpawnCountdown;

	//Keep track of pickups spawned to allow for special pickups after a certain number of spawns 
	int32 PickupTracker;
};
