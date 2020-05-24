// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "PlayerCharacter.h"
#include "Pickup.h"

APickup::APickup() :
	AActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void APickup::Spawned(float TimeoutTime)
{
	//Actual timeout time is increased to compensate for lag introduced in the way the timer for spawning is counted down
	GetWorldTimerManager().SetTimer(TimeoutTimer, this, &APickup::Timeout, TimeoutTime * 1.05f, false);
	USphereComponent* Sphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	PickupRadius = Sphere->GetScaledSphereRadius();
	TestCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

int32 APickup::GetBombCharges()
{
	return BombCharges;
}

int32 APickup::GetScore()
{
	return Score;
}


void APickup::Timeout()
{
	Destroy();
}

void APickup::PickedUp()
{
	Destroy();
}

void APickup::Tick(float deltatime)
{
	temp1 = TestCharacter->GetActorLocation();
	temp2 = GetActorLocation();
	DistanceToPlayerCharacter = FVector::Dist(temp1,temp2);
	if (DistanceToPlayerCharacter <= PickupRadius)
	{
		PickedUp();
		TestCharacter->GotPickup(this);
	}
}
/*
void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* TestCharacter = Cast<APlayerCharacter>(OtherActor);
	if (TestCharacter)
	{
		PickedUp();
		TestCharacter->GotPickup();
	}
}*/