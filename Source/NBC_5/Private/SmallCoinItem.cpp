#include "SmallCoinItem.h"

#include "SpartaGameState.h" 
#include "Kismet/GameplayStatics.h"

ASmallCoinItem::ASmallCoinItem()
{
	PointValue=10;
	ItemType="SmallCoin";
}

void ASmallCoinItem::ActivateItem(AActor* Activator)
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
