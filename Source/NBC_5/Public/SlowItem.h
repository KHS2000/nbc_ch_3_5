#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowItem.generated.h"


UCLASS()
class NBC_5_API ASlowItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ASlowItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float SlowPower;
	
	virtual void ActivateItem(AActor* Activator) override;
	
};
