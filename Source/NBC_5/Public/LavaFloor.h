#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LavaFloor.generated.h"

UCLASS()
class NBC_5_API ALavaFloor : public AActor
{
	GENERATED_BODY()
	
public:	

	ALavaFloor();
	
	UFUNCTION()
	void OnBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	void SetRiseSpeed(float NewSpeed);

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* LavaMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;
	
	
	
	UPROPERTY(EditAnywhere,Category="Lava")
	float RiseSpeed = 10.0f;
	
	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;

};
