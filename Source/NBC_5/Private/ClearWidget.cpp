#include "ClearWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "SpartaGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭 연결
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UClearWidget::OnMainMenuClicked);
	}

	// 점수 표시
	USpartaGameInstance* GI = Cast<USpartaGameInstance>(GetGameInstance());

	if (GI && ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(GI->TotalScore));
	}
}

void UClearWidget::OnMainMenuClicked()
{
	if (USpartaGameInstance* GI = Cast<USpartaGameInstance>(GetGameInstance()))
	{
		GI->ResetGameData();
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
}