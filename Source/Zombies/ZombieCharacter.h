// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ZombieCharacter.generated.h"

UCLASS()
class ZOMBIES_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	//Damage dealt to player when character when in range
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	int32 HitDamage;
	//The distance beyond the sum of player and zombie capsule radii at which the zombie can attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float HitBuffer;
private:
	//Set CanHit to true
	void ToggleCanHitOn();
	//Distance to player at which they can be hit
	float HitRadius;
	//Store for testng distance to player character each tick (for purposes of being picked up)
	class APlayerCharacter* TestCharacter;
	//Used for storing Player location and this object's location
	FVector temp1;
	FVector temp2;
	float DistanceToPlayerCharacter;
	bool CanHit;
	FTimerHandle HitTimer;
};
