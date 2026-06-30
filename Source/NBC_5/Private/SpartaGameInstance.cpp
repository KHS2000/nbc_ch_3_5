#include "SpartaGameInstance.h"

USpartaGameInstance::USpartaGameInstance()
{
	TotalScore=0;
	CurrentMapLevel=1;
}

void USpartaGameInstance::ResetGameData()
{
	TotalScore = 0;
}

void USpartaGameInstance::NextLevelMap()
{
	CurrentMapLevel+=1;
}
