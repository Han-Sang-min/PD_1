#include "TestGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestGameMode::ATestGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass(); 
}
