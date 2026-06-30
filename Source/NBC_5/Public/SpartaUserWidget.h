#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Animation/WidgetAnimation.h"
#include "SpartaUserWidget.generated.h"


class APlayerCharacter;

UCLASS()
class NBC_5_API USpartaUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void ShowWaveStart(int32 WaveIndex);


protected:
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
    
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveStartText;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* WaveStartAnim;
	
	// UFUNCTION()
	// void HideWaveStart();
	
	//FTimerHandle WaveTextTimerHandle;
};
