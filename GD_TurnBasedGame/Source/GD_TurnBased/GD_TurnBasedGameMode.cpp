// Copyright Epic Games, Inc. All Rights Reserved.

#include "GD_TurnBasedGameMode.h"
#include "GD_TurnBasedPlayerController.h"
#include "GD_TurnBasedCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGD_TurnBasedGameMode::AGD_TurnBasedGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGD_TurnBasedPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}