// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "PlayerCharacter.h"
#include "ZombieCharacter.h"


// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CanHit = true;
}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TestCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	HitRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() + TestCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius() + HitBuffer;
}

// Called every frame
void AZombieCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (CanHit)
	{
		temp1 = TestCharacter->GetActorLocation();
		temp2 = GetActorLocation();
		DistanceToPlayerCharacter = FVector::Dist(temp1, temp2);
		if (DistanceToPlayerCharacter <= HitRadius)
		{
			TestCharacter->GotHit(HitDamage);
		}
		CanHit = false;
		GetWorldTimerManager().SetTimer(HitTimer, this, &AZombieCharacter::ToggleCanHitOn, 0.5f, false);
	}
}

void AZombieCharacter::ToggleCanHitOn()
{
	CanHit = true;
}

// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

