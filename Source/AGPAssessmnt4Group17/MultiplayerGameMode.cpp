// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"

#include "EngineUtils.h"

void AMultiplayerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages)
{
	Super::InitGame(MapName, Options, ErrorMessages);

	DungeonManager = GetWorld()->SpawnActor<ADungeonManager>();
}
