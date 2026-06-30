#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "BGMManager.generated.h"

UCLASS()
class NBC_5_API ABGMManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ABGMManager();


protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UAudioComponent* AudioComponent;

	// 에디터에서 지정할 BGM
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* BGM;

public:	

	virtual void Tick(float DeltaTime) override;

};
