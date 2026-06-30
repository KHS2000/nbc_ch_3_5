#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AMineItem::AMineItem()
{
	ExplosionDelay = 5;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30;
	ItemType = "Mine";
	bHasExploded = false;
	StartTime=0;
	
	ExplosionCollision=CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);
	
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetupAttachment(ExplosionCollision);
	
	
	BaseDecalComponent=CreateDefaultSubobject<UDecalComponent>(TEXT("BaseDecalComponent"));
	BaseDecalComponent->SetupAttachment(ExplosionCollision);
	
}


void AMineItem::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterial=DecalComponent->CreateDynamicMaterialInstance();
	DynamicMaterialBase=BaseDecalComponent->CreateDynamicMaterialInstance();
	
	DecalComponent->SetVisibility(false);
	BaseDecalComponent->SetVisibility(false);
	
	if (ExplosionCollision)
	{
		ExplosionCollision->SetSphereRadius(ExplosionRadius);
	}
}


void AMineItem::ActivateItem(AActor* Activator)
{
	if (bHasExploded)return;
	
	if (Collision)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
		   GetWorld(), 
		   PickupSound, 
		   GetActorLocation()
		);
	}
	
	if (DynamicMaterial)
	{
		DecalComponent->SetVisibility(true);
		StartTime=GetWorld()->GetTimeSeconds();
		DynamicMaterial->SetScalarParameterValue(TEXT("ResetTime"), StartTime);
	}
	
	if (DynamicMaterialBase)
	{
		BaseDecalComponent->SetVisibility(true);
	}
	
	GetWorld()->GetTimerManager().SetTimer(
	ExplosionTimerHandle,
	this,
	&AMineItem::Explode,
	ExplosionDelay,
	false
	);

	bHasExploded=true;
}



void AMineItem::Explode()
{
	if (DecalComponent)
	{
		DecalComponent->SetVisibility(false);
	}
	
	if (BaseDecalComponent)
	{
		BaseDecalComponent->SetVisibility(false);
	}
	
	
	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			true
			);
	}
	
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation()
			);
	}
	
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);
	
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDamageType::StaticClass()
				);
		}
	}
	
	Super::ActivateItem(nullptr);
}
