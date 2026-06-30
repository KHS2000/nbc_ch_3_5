#include "CoinItem.h"



ACoinItem::ACoinItem()
{
	PointValue=0;
	ItemType="DefaultCoin";
}


void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
}
