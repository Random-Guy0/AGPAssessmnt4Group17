// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"

#include "EngineUtils.h"

AActor* AMultiplayerGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if(DungeonManager)
	{
		int32 RandomStart = FMath::RandRange(0, DungeonManager->PlayerStartLocations.Num() - 1);
		APlayerStart* StartLocation = DungeonManager->PlayerStartLocations[RandomStart];
		DungeonManager->PlayerStartLocations.RemoveAt(RandomStart);
		return StartLocation;
	}
	else
	{
		return Super::ChoosePlayerStart_Implementation(Player);
	}
}

void AMultiplayerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages)
{
	Super::InitGame(MapName, Options, ErrorMessages);

	DungeonManager = GetWorld()->SpawnActor<ADungeonManager>();

	if(DungeonManager)
	{
		DungeonManager->CreateDungeon();
	}

	Floor = GetWorld()->SpawnActor<AProceduralFloor>(ProceduralFloorBlueprint);
	Floor->SetSizeFloor(DungeonManager->DungeonWidth * DungeonManager->GridSize, DungeonManager->DungeonDepth * DungeonManager->GridSize);
	


}
