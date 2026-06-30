#include "BallSpawner.h"
#include "BallObstacle.h"
#include "Kismet/GameplayStatics.h"

ABallSpawner::ABallSpawner()
{
 
	PrimaryActorTick.bCanEverTick = false;

}


void ABallSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ABallSpawner::SpawnBall()
{
	if (!BallClass) return;

	if (SpawnedCount >= SpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	GetWorld()->SpawnActor<ABallObstacle>(
		BallClass,
		GetActorLocation() + SpawnLocation,
		FRotator::ZeroRotator
	);

	SpawnedCount++;
}

void ABallSpawner::StartSpawning()
{
	SpawnedCount = 0;

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ABallSpawner::SpawnBall,
		SpawnSpeed,
		true
	);
}


void ABallSpawner::SetWave(int32 WaveIndex)
{
	SpawnedCount = 0;

	if (WaveIndex == 1)
	{
		SpawnCount = 8;
		SpawnSpeed = 3;
	}
	else if (WaveIndex == 2)
	{
		SpawnCount = 10;
		SpawnSpeed = 2;
	}
	else if (WaveIndex == 3)
	{
		SpawnCount = 15;
		SpawnSpeed = 1;
	}

	StartSpawning();
}

