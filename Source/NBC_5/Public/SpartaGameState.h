#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"


UCLASS()
class NBC_5_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "GameProgress")
	int32 CurrentScore = 0;
	
	UFUNCTION(BlueprintCallable, Category = "GameProgress")
	void AddScore(int32 Amount);
	
	UPROPERTY(BlueprintReadOnly, Category = "GameProgress")
	int32 CurrentWaveIndex = 1;
	
	UPROPERTY(BlueprintReadOnly, Category = "GameProgress")
	float RemainingTime = 0.0f;
	
	UPROPERTY()
	TArray<class ABallSpawner*> BallSpawners;

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class USpartaUserWidget> HUDWidgetClass;
	
private:
	virtual void BeginPlay() override;
	
	void UpdateTimer();
	
	void MoveNextLevel();
	
	FTimerHandle WaveTimerHandle;
	
	UPROPERTY()
	class USpartaUserWidget* CurrentHUDWidget;
};
