#include "SpartaUserWidget.h"

#include "SpartaGameInstance.h"
#include "SpartaGameState.h" 
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


void USpartaUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<APlayerCharacter>(
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)
		);
	}
	
	if (PlayerCharacter && HPText)
	{
		FString HPStr = FString::Printf(TEXT("HP : %.0f"), PlayerCharacter->GetHealth());
		HPText->SetText(FText::FromString(HPStr));
	}
	
	
	if (PlayerCharacter && HPBar)
	{
		float Percent = PlayerCharacter->GetHealth()/ PlayerCharacter->GetMaxHealth();
		HPBar->SetPercent(Percent);
	}
	
	
	
	USpartaGameInstance* SpartaGI = Cast<USpartaGameInstance>(GetWorld()->GetGameInstance());
	

	if (SpartaGI && ScoreText)
	{
		//ScoreText->SetText(FText::AsNumber(SpartaGI->TotalScore));
		FString ScoreStr = FString::Printf(TEXT("점수 : %d"), SpartaGI->TotalScore);
		ScoreText->SetText(FText::FromString(ScoreStr));
	}
	
	if (SpartaGI && LevelText)
	{
		//ScoreText->SetText(FText::AsNumber(SpartaGI->TotalScore));
		FString LevelStr = FString::Printf(TEXT("레벨 : %d"), SpartaGI->CurrentMapLevel);
		LevelText->SetText(FText::FromString(LevelStr));
	}
	
	
	ASpartaGameState* GameState = Cast<ASpartaGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
	
		if (WaveText)
		{
			FString WaveStr = FString::Printf(TEXT("Wave: %d"), GameState->CurrentWaveIndex);
			WaveText->SetText(FText::FromString(WaveStr));
		}

		
		if (TimerText)
		{
			int32 IntTime = FMath::RoundToInt(GameState->RemainingTime);
			FString TimerStr = FString::Printf(TEXT("남은 시간 : %d"), IntTime);
			TimerText->SetText(FText::FromString(TimerStr));
			
			//TimerText->SetText(FText::AsNumber(IntTime));
		}
		
	}
}

void USpartaUserWidget::ShowWaveStart(int32 WaveIndex)
{
	if (WaveStartText)
	{
		FString WaveString = FString::Printf(TEXT("%d 웨이브 시작!"), WaveIndex);

		WaveStartText->SetText(FText::FromString(WaveString));

		if (WaveStartAnim)
		{
			StopAnimation(WaveStartAnim);
			PlayAnimation(WaveStartAnim);
		}
		
		// GetWorld()->GetTimerManager().ClearTimer(WaveTextTimerHandle);
		//
		// GetWorld()->GetTimerManager().SetTimer(
		// 	WaveTextTimerHandle,
		// 	this,
		// 	&USpartaUserWidget::HideWaveStart,
		// 	2.0f,
		// 	false
		// );
	}
}

// void USpartaUserWidget::HideWaveStart()
// {
// 	if (WaveStartText)
// 	{
// 		WaveStartText->SetVisibility(ESlateVisibility::Hidden);
// 	}
// }

