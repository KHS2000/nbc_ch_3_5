#include "SlowItem.h"

#include "PlayerCharacter.h"

ASlowItem::ASlowItem()
{
	SlowPower=0.5f;
	ItemType="SlowTime";
}


void ASlowItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (Activator&&Activator->ActorHasTag("Player"))
	{
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator))
		{
			PlayerCharacter->SlowTime(SlowPower);
		}
		//DestroyItem();
	}
}
