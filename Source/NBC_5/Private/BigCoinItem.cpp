#include "BigCoinItem.h"

#include "SpartaGameState.h" 
#include "Kismet/GameplayStatics.h"

ABigCoinItem::ABigCoinItem()
{
	PointValue = 50;
	ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (GetWorld())
	{
		ASpartaGameState* GameState = Cast<ASpartaGameState>(GetWorld()->GetGameState());
		
		if (GameState)
		{
			GameState->AddScore(PointValue);
		}
	}
}

