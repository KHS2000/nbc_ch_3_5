#include "GameOverWidget.h"
#include "MyPlayerController.h"

#include "SpartaGameInstance.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(
			this,
			&UGameOverWidget::RestartButtonClicked
			);
	}
	
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(
			this,
			&UGameOverWidget::MainMenuButtonClicked
			);
	}
}

void UGameOverWidget::RestartButtonClicked()
{
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (PC)
	{
		PC->RestartGame();
	}
}

void UGameOverWidget::RemoveGameOverUI()
{
	RemoveFromParent();
}

void UGameOverWidget::MainMenuButtonClicked()
{
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (PC)
	{
		if (USpartaGameInstance* GI = Cast<USpartaGameInstance>(GetGameInstance()))
		{
			GI->ResetGameData();   // ← 여기서 초기화
		}

		PC->OpenMainMenu();
	}
}


void UGameOverWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	USpartaGameInstance* SpartaGI = Cast<USpartaGameInstance>(GetWorld()->GetGameInstance());
	
	if (SpartaGI && ScoreText)
	{
		//ScoreText->SetText(FText::AsNumber(SpartaGI->TotalScore));
		FString ScoreStr = FString::Printf(TEXT("점수 : %d"), SpartaGI->TotalScore);
		ScoreText->SetText(FText::FromString(ScoreStr));
	}
}
