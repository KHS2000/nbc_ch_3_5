#include "SpartaGameState.h"

#include "SpartaGameInstance.h"
#include "SpartaUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"
#include "BallSpawner.h"
#include "LavaFloor.h"
#include "EngineUtils.h"
#include "GroundSpike.h"
#include "Kismet/GameplayStatics.h"  //맵이동 함수사용을 위해


void ASpartaGameState::AddScore(int32 Amount)
{
	USpartaGameInstance* SpartaGI = Cast<USpartaGameInstance>(GetGameInstance());
	
	if (SpartaGI)
	{
		SpartaGI->TotalScore += Amount;
        
		UE_LOG(LogTemp, Log, TEXT(" 동전 획득! 현재 총점: %d 점"), SpartaGI->TotalScore);
	}
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentWaveIndex = 1;
	RemainingTime = 30.0f;
	
	UE_LOG(LogTemp, Warning, TEXT("=== 게임 시작! 1웨이브 (%d초) 버티기 ==="), FMath::RoundToInt(RemainingTime));

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&ASpartaGameState::UpdateTimer,
			1.0f,
			true
		);
	}
	
	if (HUDWidgetClass)
	{
		CurrentHUDWidget = CreateWidget<USpartaUserWidget>(GetWorld(), HUDWidgetClass);
        

		if (CurrentHUDWidget)
		{
			CurrentHUDWidget->AddToViewport();
			
			CurrentHUDWidget->ShowWaveStart(CurrentWaveIndex);
		}
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		// 1. 마우스 커서를 다시 화면에서 숨깁니다.
		PC->bShowMouseCursor = false;

		// 2. 입력 모드를 '게임 플레이 전용'으로 전환하여 캐릭터가 움직이도록 만듭니다.
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
	
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABallSpawner::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		BallSpawners.Add(Cast<ABallSpawner>(Actor));
	}
	
	for (ABallSpawner* Spawner : BallSpawners)
	{
		if (Spawner)
		{
			Spawner->SetWave(1);
		}
	}
}

void ASpartaGameState::UpdateTimer()
{
	
	if (RemainingTime > 0.0f)
	{
		RemainingTime -= 1.0f;
		UE_LOG(LogTemp, Log, TEXT("%d 웨이브 진행 중... 남은 시간: %d 초"), CurrentWaveIndex, FMath::RoundToInt(RemainingTime));
	}
	else
	{
		if (CurrentWaveIndex == 1)
		{
			CurrentWaveIndex = 2;
			RemainingTime = 25.0f;
			
			if (CurrentHUDWidget)
			{
				CurrentHUDWidget->ShowWaveStart(CurrentWaveIndex);
			}
			
			UE_LOG(LogTemp, Warning, TEXT(" 1웨이브 성공! === 2웨이브 (%d초) 시작 ==="), FMath::RoundToInt(RemainingTime));
			
			
			for (TActorIterator<AGroundSpike>It(GetWorld());It;++It)
			{
				It->SetSpikeSpeed(900.f);
			}
			
			for (TActorIterator<ALavaFloor> It(GetWorld()); It; ++It)
			{
				It->SetRiseSpeed(120.0f);
			}
			
			
			for (ABallSpawner* Spawner : BallSpawners)
			{
				if (Spawner)
				{
					Spawner->SetWave(CurrentWaveIndex);
				}
			}
		}
		else if (CurrentWaveIndex == 2)
		{
			CurrentWaveIndex = 3;
			RemainingTime = 20.0f;
			
			if (CurrentHUDWidget)
			{
				CurrentHUDWidget->ShowWaveStart(CurrentWaveIndex);
			}
			
			
			UE_LOG(LogTemp, Warning, TEXT(" 2웨이브 성공! === 마지막 3웨이브 (%d초) 시작 ==="), FMath::RoundToInt(RemainingTime));
			
			
			
			for (TActorIterator<AGroundSpike>It(GetWorld());It;++It)
			{
				It->SetSpikeSpeed(1200.f);
			}
			
			for (TActorIterator<ALavaFloor> It(GetWorld()); It; ++It)
			{
				It->SetRiseSpeed(200.0f);
			}
			
			for (ABallSpawner* Spawner : BallSpawners)
			{
				if (Spawner)
				{
					Spawner->SetWave(CurrentWaveIndex);
				}
			}
			
		}
		else if (CurrentWaveIndex == 3)
		{
			MoveNextLevel();
		}
	}
}

void ASpartaGameState::MoveNextLevel()
{
	USpartaGameInstance* SpartaGIL = Cast<USpartaGameInstance>(GetGameInstance());
	
	if (GetWorld())
	{
		if (SpartaGIL)
		{
			if (SpartaGIL->CurrentMapLevel==1)
			{
				GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
                
				UE_LOG(LogTemp, Warning, TEXT(" [레벨 1] 모든 웨이브 클리어!! 레벨 2 맵으로 이동합니다."));
				
				SpartaGIL->CurrentMapLevel+=1;
				
				UGameplayStatics::OpenLevel(GetWorld(), FName("Level2"));
			}
			else if (SpartaGIL->CurrentMapLevel==2)
			{
				GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
                
				UE_LOG(LogTemp, Warning, TEXT(" [레벨 2] 모든 웨이브 클리어!! 레벨 3 맵으로 이동합니다."));
				
				SpartaGIL->CurrentMapLevel+=1;
				
				UGameplayStatics::OpenLevel(GetWorld(), FName("Level3"));
			}
			else if (CurrentWaveIndex == 3)
			{
				GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);

				UGameplayStatics::OpenLevel(GetWorld(), FName("GameClearLevel"));
			}
			
		}
		
		
	}
}
