// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_API APickup : public AActor
{
	GENERATED_BODY()
	
public:
	APickup();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void Spawned(float TimeoutTime);

	//Returns the number of bomb charges that should be added when picked up
	UFUNCTION(BlueprintPure, Category = "Pickup")
	int32 GetBombCharges();
	//Returns the point score that should be added when picked up
	UFUNCTION(BlueprintPure, Category = "Pickup")
	int32 GetScore();
	
	virtual void Tick(float DeltaSeconds) override;
protected:
	void Timeout();
	FTimerHandle TimeoutTimer;
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void PickedUp();
	//the number of bomb charges that should be added when picked up
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
	int32 BombCharges;
	//the point score that should be added when picked up
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
	int32 Score;

private:
	//Store for testng distance to player character each tick (for purposes of being picked up)
	class APlayerCharacter* TestCharacter;
	//Distance to player under which this pickup will be picked up
	float PickupRadius;
	//Used for storing Player location and this object's location
	FVector temp1;
	FVector temp2;
	float DistanceToPlayerCharacter;
	//UFUNCTION(Category = "Collision")
	//void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
