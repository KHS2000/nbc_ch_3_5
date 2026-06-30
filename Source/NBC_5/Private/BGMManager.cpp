#include "BGMManager.h"

#include "Components/AudioComponent.h"


ABGMManager::ABGMManager()
{

	PrimaryActorTick.bCanEverTick = true;
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = AudioComponent;

	// BeginPlay에서 직접 재생할 것이므로 자동 재생은 끔
	AudioComponent->bAutoActivate = false;

}


void ABGMManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (BGM)
	{
		AudioComponent->SetSound(BGM);
		AudioComponent->Play();
	}
}


void ABGMManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

