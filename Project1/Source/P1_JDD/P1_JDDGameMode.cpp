// Copyright Epic Games, Inc. All Rights Reserved.

#include "P1_JDDGameMode.h"
#include "P1_JDDPawn.h"

AP1_JDDGameMode::AP1_JDDGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AP1_JDDPawn::StaticClass();
}
