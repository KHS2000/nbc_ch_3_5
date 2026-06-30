#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClearWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class NBC_5_API UClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION()
	void OnMainMenuClicked();
};
