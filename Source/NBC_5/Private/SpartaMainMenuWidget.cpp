#include "SpartaMainMenuWidget.h"

#include "SpartaGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool USpartaMainMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &USpartaMainMenuWidget::OnStartClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &USpartaMainMenuWidget::OnQuitClicked);
	}

	return true;
}

void USpartaMainMenuWidget::OnStartClicked()
{

	UGameplayStatics::OpenLevel(GetWorld(), FName("Level1"));
}

void USpartaMainMenuWidget::OnQuitClicked()
{
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, false);
}

void USpartaMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Level1Button->OnClicked.AddDynamic(this, &USpartaMainMenuWidget::OnLevel1ButtonClicked);
	Level2Button->OnClicked.AddDynamic(this, &USpartaMainMenuWidget::OnLevel2ButtonClicked);
	Level3Button->OnClicked.AddDynamic(this, &USpartaMainMenuWidget::OnLevel3ButtonClicked);
}

void USpartaMainMenuWidget::OnLevel1ButtonClicked()


{
	UGameplayStatics::OpenLevel(this, FName("Level1"));
}

void USpartaMainMenuWidget::OnLevel2ButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Level2"));
}

void USpartaMainMenuWidget::OnLevel3ButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Level3"));
}