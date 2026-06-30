#include "BallObstacle.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


ABallObstacle::ABallObstacle()
{
 
	PrimaryActorTick.bCanEverTick = false;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetEnableGravity(true);
	SphereCollision->SetCollisionProfileName(TEXT("PhysicsActor"));
	// SphereCollision->SetNotifyRigidBodyCollision(true);
	

	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(SphereCollision);
	BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallMesh->SetSimulatePhysics(false);

}


void ABallObstacle::BeginPlay()
{
	Super::BeginPlay();
	

	SphereCollision->OnComponentBeginOverlap.AddDynamic(
	this,
	&ABallObstacle::OnBallOverlap
);
	
}


void ABallObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ABallObstacle::OnBallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		UGameplayStatics::ApplyDamage(
			Player,
			10.0f,
			nullptr,
			this,
			UDamageType::StaticClass()
		);
		
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation()
			);
		}

		
		FVector LaunchDir = Player->GetActorLocation() - GetActorLocation();
		LaunchDir.Z = 0.5f; // 살짝 위로 띄움
		LaunchDir.Normalize();

		Player->LaunchCharacter(LaunchDir * 1000.0f, true, true);
	}
}

