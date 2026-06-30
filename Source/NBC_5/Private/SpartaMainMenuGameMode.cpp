#include "SpartaMainMenuGameMode.h"
#include "SpartaMainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void ASpartaMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{

		PC->bShowMouseCursor = true;
        

		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}


	if (MainMenuWidgetClass)
	{

		USpartaMainMenuWidget* MainMenuWidget = CreateWidget<USpartaMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
