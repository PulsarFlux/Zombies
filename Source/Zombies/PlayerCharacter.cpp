// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "ZombiesGameMode.h"
#include "ZombieCharacter.h"
#include "Pickup.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	BombCharges = 0;
	Score = 0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	BombExplosionSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	CurrentHealth = InitialHealth;
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAction("DetonateBomb", IE_Pressed, this, &APlayerCharacter::DetonateBomb);
	(InputComponent->BindAction("Quit", IE_Pressed, this, &APlayerCharacter::QuitTheGame)).bExecuteWhenPaused = true;;
	(InputComponent->BindAction("Restart", IE_Pressed, this, &APlayerCharacter::RestartTheGame)).bExecuteWhenPaused = true;
}

int32 APlayerCharacter::GetCurrentHealth()
{
	return CurrentHealth;
}

int32 APlayerCharacter::GetNumBombCharges()
{
	return BombCharges;
}

int32 APlayerCharacter::GetCurrentScore()
{
	return Score;
}

void APlayerCharacter::GotPickup(APickup* ThePickup)
{
	BombCharges += ThePickup->GetBombCharges();
	Score += ThePickup->GetScore();
}

void APlayerCharacter::GotHit(int32 Damage)
{
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0)
		{
			CurrentHealth = 0;
			AZombiesGameMode* GameMode = Cast<AZombiesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GameMode)
			{
				GameMode->GameOver();
			}
		}
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// get forward vector
		const FVector Direction = FVector(1.0f, 0.0f, 0.0f);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// get right vector
		const FVector Direction = FVector(0.0f, 1.0f, 0.0f);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::SetDestroyableBlockType(TSubclassOf<AActor> BlockType)
{
	DestroyableBlock = BlockType;
}

void APlayerCharacter::DetonateBomb()
{
	if (BombCharges > 0)
	{
		BombCharges -= 1;
		TArray<AActor*> HitBlocks;
		BombExplosionSphere->GetOverlappingActors(HitBlocks, DestroyableBlock);
		for (int i = 0; i < HitBlocks.Num(); i++)
		{
				HitBlocks[i]->Destroy();
		}
		TArray<AActor*> HitZombies;
		BombExplosionSphere->GetOverlappingActors(HitZombies, AZombieCharacter::StaticClass());
		for (int i = 0; i < HitZombies.Num(); i++)
		{
			HitZombies[i]->Destroy();
		}
	}
}

void APlayerCharacter::RestartTheGame()
{
	AZombiesGameMode* GameMode = Cast<AZombiesGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->RestartTheGame();
	}
}

void APlayerCharacter::QuitTheGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit);
}


