#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}
