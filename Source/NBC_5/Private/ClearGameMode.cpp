#include "ClearGameMode.h"

#include "SpartaGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void AClearGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (ClearWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ClearWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(nullptr);
		PC->SetInputMode(InputMode);
	}
}

