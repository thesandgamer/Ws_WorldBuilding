// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnPoint.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnGroup.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct WS_WORLDBUILDING_API FMyAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> actorToSpawn;

	UPROPERTY(EditAnywhere)
		TArray<ASpawnPoint*> spawnpoints;
};

UCLASS()
class WS_WORLDBUILDING_API ASpawnGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnGroup();

	UPROPERTY(EditAnywhere)
		uint8 bAutoSpawn : 1;

	UPROPERTY(EditAnywhere)
		uint16 itemsSpawnMin;

	UPROPERTY(EditAnywhere)
		uint16 itemsSpawnMax;

	UPROPERTY(EditAnywhere)
		TArray<FMyAsset> items;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DoSpawning();
};
