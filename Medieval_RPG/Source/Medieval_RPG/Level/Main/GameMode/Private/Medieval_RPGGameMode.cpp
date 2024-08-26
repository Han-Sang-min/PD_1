// Copyright Epic Games, Inc. All Rights Reserved.

#include "Medieval_RPGGameMode.h"
#include "Medieval_RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMedieval_RPGGameMode::AMedieval_RPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
