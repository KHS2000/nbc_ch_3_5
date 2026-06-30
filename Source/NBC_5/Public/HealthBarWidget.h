#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"


class UProgressBar;

UCLASS()
class NBC_5_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealthPercent(float Percent);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	
};
