#include "GroundSpike.h"

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


AGroundSpike::AGroundSpike()
{

	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent=SceneComponent;
	
	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(StaticMeshComponent);
	
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetupAttachment(StaticMeshComponent);
	

	
	
	FindTime=0.3f;
	SpikeDelay=0.1f;
	SpikeUptime=0.5f;
	SpikeDamage=5.0f;

}


void AGroundSpike::BeginPlay()
{
	Super::BeginPlay();
	
	 CapsuleComponent->OnComponentBeginOverlap.AddDynamic(
	 	this,
		&AGroundSpike::OnOverlapBegin
	 	);
	
	
	GetWorldTimerManager().SetTimer(
	SpikeChaceTimerHandle,
	this,
	&AGroundSpike::StartFindPlayer,
	2.0f,
	false);
	
}


void AGroundSpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (!isUp)
	{
		return;
	}
	
	
	FVector CurrentLocation=GetActorLocation();
	
	if (CurrentLocation.Z<UpLocation.Z)
	{
		CurrentLocation.Z+=MoveSpeed*DeltaTime;
		
		if (CurrentLocation.Z > UpLocation.Z)
		{
			CurrentLocation.Z = UpLocation.Z;
		}
		
		
		SetActorLocation(CurrentLocation);
	}
	
}

void AGroundSpike::FindPlayer()
{
	if (isUp)
	{
		return;
	}
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter)
	{
		FVector FindPlayerLocation = PlayerCharacter->GetActorLocation();
		
		FindPlayerLocation.Z-=350.f;
		
		FindPlayerLocation.Z+=SpikeLocation;
		
		SetActorLocation(FindPlayerLocation);
		
		
		FTimerHandle SpikeDelayTimer;
		GetWorldTimerManager().SetTimer(
			SpikeDelayTimer,
			this,
			&AGroundSpike::RiseSpike,
			SpikeDelay,
			false);
		
	}
}

void AGroundSpike::RiseSpike()
{
	isUp=true;
	
	DownLocation = GetActorLocation();
	
	UpLocation=DownLocation;
	UpLocation.Z+=200.f;
	
	FTimerHandle ResetTimerHandle;
	GetWorldTimerManager().SetTimer(
		ResetTimerHandle,[this]()
		{
			if (!IsValid(this)) return;
			isUp=false;
		},
		SpikeUptime,
		false);
	
}

void AGroundSpike::OnOverlapBegin(
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
		UGameplayStatics::ApplyDamage(
			Player,      // 데미지를 받을 액터
			SpikeDamage,        // 데미지 양
			nullptr,     // 공격한 Controller
			this,        // 데미지를 준 액터(가시)
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

		
		FVector LaunchDirection = FVector(
		FMath::RandBool() ? 1.f : -1.f,
		FMath::RandBool() ? 1.f : -1.f,
		0.f
		);

		LaunchDirection.Normalize();

		Player->LaunchCharacter(LaunchDirection * 2500.f, true, false);
	}
	
}

void AGroundSpike::SetSpikeSpeed(float speed)
{
	MoveSpeed=speed;
}

void AGroundSpike::StartFindPlayer()
{
	GetWorldTimerManager().SetTimer(
		SpikeChaceTimerHandle,
		this,
		&AGroundSpike::FindPlayer,
		FindTime,
		true);
}
