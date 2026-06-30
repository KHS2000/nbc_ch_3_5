#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"		//IMC를 위한 헤더 추가
#include "WaveStartWidget.h"
#include "MyPlayerController.generated.h"


UCLASS()
class NBC_5_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	
	virtual void BeginPlay() override;
	
	void GameOver();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>GameOverWidgetClass;
	
	UFUNCTION(BlueprintCallable)
	void RestartGame();
	
	UFUNCTION(BlueprintCallable)
	void OpenMainMenu();

	

protected:


	
private:
	
	UPROPERTY(EditAnywhere)   //IMC리플렉션
	UInputMappingContext* MappingContext;
	
	bool bIsGameOver=false;
};
