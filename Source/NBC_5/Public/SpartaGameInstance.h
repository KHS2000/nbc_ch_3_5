#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpartaGameInstance.generated.h"


UCLASS()
class NBC_5_API USpartaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	USpartaGameInstance();
	
	void ResetGameData();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentMapLevel;
	
	void NextLevelMap();
};
