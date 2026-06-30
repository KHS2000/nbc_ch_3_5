#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SpinCameraItem.generated.h"


UCLASS()
class NBC_5_API ASpinCameraItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ASpinCameraItem();
	
	virtual void ActivateItem(AActor* Activator) override;
	
};
