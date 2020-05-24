// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombies.h"
#include "BlockSpawnVolume.h"

// Sets default values
ABlockSpawnVolume::ABlockSpawnVolume()
	: ASpawnVolume()
{

}

void ABlockSpawnVolume::SpawnObject(TSubclassOf<AActor> WhatToSpawn)
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Assuming WhatToSpawn can be cast to AStaticMeshActor find the 'width' (x component) of its static mech bounding box times the transform scale and store it in BlockWidth
			UStaticMeshComponent* TempMesh = WhatToSpawn->GetDefaultObject<AStaticMeshActor>()->GetStaticMeshComponent();
			float BlockWidth = (((TempMesh->StaticMesh)->GetBoundingBox()).GetSize()).X * TempMesh->GetRelativeTransform().GetScale3D().X;

			//Capsule component of the player character
			UCapsuleComponent* PlayerCapsule = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCapsuleComponent();
			//Find the bound box corresponding to the player capsule
			FBox PlayerBoundingBox = PlayerCapsule->CalcBounds(PlayerCapsule->GetRelativeTransform()).GetBox();

			FVector SpawnLocation = FVector(0,0,0);
			//Generate spawn locations until the blocks will not overlap with the player character
			bool Overlap = true;
			while (Overlap)
			{
				SpawnLocation = GetRandomPointInVolume();
				SpawnLocation.X = BlockWidth * FMath::Trunc(SpawnLocation.X / BlockWidth);
				SpawnLocation.Y = BlockWidth * FMath::Trunc(SpawnLocation.Y / BlockWidth);
				SpawnLocation.Z = SpawnBox->Bounds.Origin.Z;
				//An FBox which represents the XY area (with arbitrary non-zero height to make it a volume) that would be taken up by by spawning blocks at the SpawnLocation
				FBox SpawnObjectVolume = FBox(SpawnLocation, SpawnLocation + FVector(SpawnGroupWidth * BlockWidth, SpawnGroupWidth * BlockWidth, 100));
				//Check if player and blocks will overlap then set Overlap to false if not
				if (!PlayerBoundingBox.Intersect(SpawnObjectVolume)) { Overlap = false; }
			}

			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0;
			SpawnRotation.Pitch = 0;
			SpawnRotation.Roll = 0;

			TArray<AActor*> ExistingBlocks;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), WhatToSpawn, ExistingBlocks);

			FVector SpawnDisplacement = FVector(0,0,0);
			for (int32 i = 0; i < SpawnGroupWidth; i++)
			{
				for (int32 k = 0; k < SpawnGroupWidth; k++)
				{
					SpawnDisplacement.Set(i * BlockWidth, k * BlockWidth, 0);
					AActor* SpawnedBlock = World->SpawnActor<AActor>(WhatToSpawn, SpawnLocation + SpawnDisplacement, SpawnRotation, SpawnParams);
					HandleBlockBlockOverlap(SpawnedBlock, ExistingBlocks);
				}
			}

		}
	}
}

void ABlockSpawnVolume::HandleBlockBlockOverlap(AActor* BlockToCheck, TArray<AActor*> ExistingBlocks)
{
	FBox BoxToCheck = Cast<AStaticMeshActor>(BlockToCheck)->GetStaticMeshComponent()->StaticMesh->GetBoundingBox();
	//Shift by location of actor since bounding box above is automatically created at the origin
	BoxToCheck = BoxToCheck.ShiftBy(BlockToCheck->GetActorTransform().GetLocation());
	int32 Counter = 0;
	bool Continue = true;
	while (Counter < ExistingBlocks.Num() && Continue)
	{
		FBox ExistingBlock = Cast<AStaticMeshActor>(ExistingBlocks[Counter])->GetStaticMeshComponent()->StaticMesh->GetBoundingBox();
		//Shift as above
		ExistingBlock = ExistingBlock.ShiftBy((ExistingBlocks[Counter])->GetActorTransform().GetLocation());
		if (BoxToCheck.Intersect(ExistingBlock)) 
		{
			Continue = false; 
			BlockToCheck->Destroy();
		}
		Counter++;
	}
}
