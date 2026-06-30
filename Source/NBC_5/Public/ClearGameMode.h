#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ClearGameMode.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class NBC_5_API AClearGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UUserWidget> ClearWidgetClass;
	
	
};
