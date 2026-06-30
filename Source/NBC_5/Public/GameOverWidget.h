#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameOverWidget.generated.h"



UCLASS()
class NBC_5_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	void RemoveGameOverUI();
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
protected:
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;
	
	UFUNCTION()
	void RestartButtonClicked();
	
	UFUNCTION()
	void MainMenuButtonClicked();
	
};
