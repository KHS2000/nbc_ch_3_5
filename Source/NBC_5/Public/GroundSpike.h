#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundSpike.generated.h"

class UCapsuleComponent;

UCLASS()
class NBC_5_API AGroundSpike : public AActor
{
	GENERATED_BODY()
	
public:	

	AGroundSpike();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spike")
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spike")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spike")
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDecalComponent* DecalComponent;
	
	FTimerHandle SpikeChaceTimerHandle;
	FTimerHandle SpikeUpTimerHandle;
	
	bool isUp=false;
	
	
	
	FVector DownLocation;
	FVector UpLocation;
	
	UPROPERTY(EditAnywhere,Category="Spike Setting")
	float MoveSpeed=500.f;

	float SpikeDamage;
	
	UFUNCTION()
	void StartFindPlayer();
	
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* HitSound;
public:	
	
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	virtual void Tick(float DeltaTime) override;
	
	void FindPlayer();
	
	void RiseSpike();
	
	float FindTime;
	float SpikeDelay;
	float SpikeUptime;
	
	float SpikeLocation;
	
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	void SetSpikeSpeed(float speed);
	

};
