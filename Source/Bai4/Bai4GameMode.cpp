// Copyright Epic Games, Inc. All Rights Reserved.

#include "Bai4GameMode.h"
#include "Bai4PlayerController.h"
#include "Bai4Character.h"
#include "UObject/ConstructorHelpers.h"

ABai4GameMode::ABai4GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABai4PlayerController::StaticClass();

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