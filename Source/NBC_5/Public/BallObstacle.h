#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "BallObstacle.generated.h"

UCLASS()
class NBC_5_API ABallObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallObstacle();
	
	// UFUNCTION()
	// void OnBallHit(
	// 	UPrimitiveComponent* HitComponent,
	// 	AActor* OtherActor,
	// 	UPrimitiveComponent* OtherComp,
	// 	FVector NormalImpulse,
	// 	const FHitResult& Hit
	// );
	
	UFUNCTION()
	void OnBallOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* HitSound;


protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* BallMesh;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;
	
	


public:	
	virtual void Tick(float DeltaTime) override;

};
