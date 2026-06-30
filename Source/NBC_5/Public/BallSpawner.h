#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallSpawner.generated.h"

UCLASS()
class NBC_5_API ABallSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	ABallSpawner();

protected:

	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<class ABallObstacle> BallClass;
	
	UPROPERTY(EditAnywhere, Category="Spawn")
	FVector SpawnLocation;
	
	UPROPERTY(EditAnywhere, Category="Wave")
	int32 SpawnCount = 3;

	int32 SpawnedCount = 0;
	
	float SpawnSpeed=0.f;
	
	void SetWave(int32 WaveIndex);
	
	
	
private:
	FTimerHandle SpawnTimerHandle;
	
	void StartSpawning();
	void SpawnBall();

};
