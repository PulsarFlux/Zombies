// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ZOMBIES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void SetDestroyableBlockType(TSubclassOf<AActor> BlockType);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	int32 InitialHealth;

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category = "Bombs")
	int32 GetNumBombCharges();

	UFUNCTION(BlueprintPure, Category = "Bombs")
	int32 GetCurrentScore();

	void GotPickup(class APickup* ThePickup);

	void GotHit(int32 Damage);

protected:
	int32 CurrentHealth;
	int32 BombCharges;
	int32 Score;
	TSubclassOf<AActor> DestroyableBlock;
	USphereComponent* BombExplosionSphere;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void DetonateBomb();
	void RestartTheGame();
private:
	void QuitTheGame();
};
