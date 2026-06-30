#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;


UCLASS()
class NBC_5_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnVolume();
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
	USceneComponent* Scene;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
	UBoxComponent* SpawningBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning")
	UDataTable* ItemDataTable;
	
	UFUNCTION(BlueprintCallable, Category="Spawning")
	AActor* SpawnRandomItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 MaxSpawnCount;

	FItemSpawnRow* GetRandomItem() const;
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume() const;

};
