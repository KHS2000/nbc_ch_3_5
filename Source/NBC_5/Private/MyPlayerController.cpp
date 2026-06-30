#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "SpartaGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AMyPlayerController::AMyPlayerController()
{
	
}


void AMyPlayerController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{	
		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void AMyPlayerController::GameOver()
{
	if (bIsGameOver)
	{
		return;
	}
	
	
	bIsGameOver=true;
	
	if (GameOverWidgetClass)
	{
		UUserWidget* GameOverWidget=CreateWidget<UUserWidget>(this,GameOverWidgetClass);
		
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
	
	SetPause(true);
	
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	bShowMouseCursor = true;
}


void AMyPlayerController::RestartGame()
{
	SetPause(false);
	
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
	
	USpartaGameInstance* GI = Cast<USpartaGameInstance>(GetGameInstance());

	// if (GI)
	// {
	// 	GI->ResetGameData();
	// }
	
	UGameplayStatics::OpenLevel(
		this,
		FName(*GetWorld()->GetName())
		);
	
}

void AMyPlayerController::OpenMainMenu()
{
	SetPause(false);

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
	
	USpartaGameInstance* GI = Cast<USpartaGameInstance>(GetGameInstance());

	if (GI)
	{
		GI->ResetGameData();
	}
	
	UGameplayStatics::OpenLevel(this, "MainMenuLevel");
}

