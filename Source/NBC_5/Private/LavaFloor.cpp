#include "LavaFloor.h"
#include "PlayerCharacter.h"



ALavaFloor::ALavaFloor()
{
 
	PrimaryActorTick.bCanEverTick = true;
	
	LavaMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LavaMesh"));
	RootComponent=LavaMesh;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

}


void ALavaFloor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&ALavaFloor::OnBoxBeginOverlap
	);
	
}

void ALavaFloor::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		Player->OnDeath();
		
		BoxCollision->SetGenerateOverlapEvents(false);
	}
}


void ALavaFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.Z += RiseSpeed*DeltaTime;
	SetActorLocation(NewLocation);
}



void ALavaFloor::SetRiseSpeed(float NewSpeed)
{
	RiseSpeed = NewSpeed;
}

