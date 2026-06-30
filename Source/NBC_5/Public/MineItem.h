#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Components/DecalComponent.h"
#include "MineItem.generated.h"


UCLASS()
class NBC_5_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AMineItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Effects")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Effects")
	USoundBase* ExplosionSound;
	
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;//폭발 활성화 차는 머티리얼
	
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterialBase;//폭발 활성화 경고 머티리얼
	
	float StartTime;
	
	bool bHasExploded;
	
	FTimerHandle ExplosionTimerHandle;
	
	void Explode();

	virtual void BeginPlay() override;

	virtual void ActivateItem(AActor* Activator) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDecalComponent* DecalComponent;//폭발 활성화 차는 머티리얼
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDecalComponent* BaseDecalComponent;//폭발 활성화 경고 머티리얼
};
