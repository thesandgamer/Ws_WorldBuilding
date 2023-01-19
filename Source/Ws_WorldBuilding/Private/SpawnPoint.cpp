// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(sceneRoot);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::DoSpawn(TSubclassOf<AActor> toSpawn) {
	UWorld* const w = GetWorld();
	FActorSpawnParameters p;
	p.Instigator = GetInstigator();
	p.Owner = GetOwner();
	w->SpawnActor<AActor>(toSpawn, GetActorLocation(), GetActorRotation(), p);
}