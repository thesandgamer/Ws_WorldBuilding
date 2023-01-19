// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGroup.h"

// Sets default values
ASpawnGroup::ASpawnGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnGroup::BeginPlay()
{
	Super::BeginPlay();
	if (bAutoSpawn) {
		DoSpawning();
	}
	
}

// Called every frame
void ASpawnGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnGroup::DoSpawning()
{
	int32 numItems = FMath::RandRange(itemsSpawnMin, itemsSpawnMax);
	TArray<FMyAsset> itemPool = items;

	TSet<ASpawnPoint*> dirtySpawns; // Dirty >:(

	for (int32 itC = 0; itC < numItems && itemPool.Num();) {
		uint32 itemIx = FMath::RandRange(0, itemPool.Num() - 1);
		FMyAsset t = itemPool[itemIx];
		itemPool.RemoveAt(itemIx);

		if (t.actorToSpawn == NULL || t.spawnpoints.Num() == 0) {
			UE_LOG(LogTemp, Warning, TEXT("Item spawn skipped because actor is null or empty spawnpoints."));
			continue;
		}

		auto spawnPool = t.spawnpoints;
		ASpawnPoint* targetSpawn = nullptr;
		while (spawnPool.Num() > 0) {
			uint32 spawnIx = FMath::RandRange(0, spawnPool.Num() - 1);
			ASpawnPoint* s = spawnPool[spawnIx];
			if (!dirtySpawns.Contains(s)) {
				dirtySpawns.Add(s);
				targetSpawn = s;
				break;
			}
			spawnPool.RemoveAt(spawnIx);
		}

		if (targetSpawn != nullptr) {
			targetSpawn->DoSpawn(t.actorToSpawn);
			++itC;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Item spawn skipped because no Itemspawn could be found."));
		}
	}
}