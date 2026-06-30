#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpartaMainMenuGameMode.generated.h"


UCLASS()
class NBC_5_API ASpartaMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	// 🎨 에디터(블루프린트 등)에서 어떤 메인메뉴 위젯을 띄울지 고르는 방입니다.
	// 방금 만든 USpartaMainMenuWidget 타입을 안전하게 포인터로 쓰기 위해 class 적어줍니다 (전방선언).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class USpartaMainMenuWidget> MainMenuWidgetClass;

	// 💡 맵이 열리자마자 "UI 띄우고 마우스 켜라!"라고 명령을 내릴 함수입니다.
	virtual void BeginPlay() override;
};
