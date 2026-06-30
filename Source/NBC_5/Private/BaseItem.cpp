#include "BaseItem.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ABaseItem::ABaseItem()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Scene);

	
	Collision->OnComponentBeginOverlap.AddDynamic(this,&ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this,&ABaseItem::OnItemEndOverlap);

}

void ABaseItem::OnItemOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	
	
	
	if (OtherActor&&OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!!!!!!")));
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}


void ABaseItem::ActivateItem(AActor* Activator)
{
	
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetVisibility(false);

	
	if (PickupParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), PickupParticle, GetActorLocation(), GetActorRotation(), true
		); 
	}
    
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	}
    
	
	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DestroyTimerHandle,
		this,
		&ABaseItem::DestroyItem, 
		2.0f,                    
		false
	);
}


FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
	
}

