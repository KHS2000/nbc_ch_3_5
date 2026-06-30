#include "SpinCameraItem.h"

#include "PlayerCharacter.h"

ASpinCameraItem::ASpinCameraItem()
{
	ItemType = "SpinCamera";
}

void ASpinCameraItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (Activator&&Activator->ActorHasTag("Player"))
	{
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator))
		{
			PlayerCharacter->StartSpinCameraEffect(5.0f);
		}
	
	}
}
