#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SpartaMainMenuWidget.generated.h"


UCLASS()
class NBC_5_API USpartaMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Level1Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Level2Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Level3Button;

	
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();
	
	UFUNCTION()
	void OnLevel1ButtonClicked();

	UFUNCTION()
	void OnLevel2ButtonClicked();

	UFUNCTION()
	void OnLevel3ButtonClicked();
};
