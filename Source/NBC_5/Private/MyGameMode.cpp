#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "PlayerCharacter.h"


AMyGameMode::AMyGameMode()
{
	DefaultPawnClass=APlayerCharacter::StaticClass();
	PlayerControllerClass=AMyPlayerController::StaticClass();
}

