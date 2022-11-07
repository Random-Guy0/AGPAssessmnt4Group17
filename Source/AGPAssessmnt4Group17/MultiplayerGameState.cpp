// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameState.h"

#include "Net/UnrealNetwork.h"

AMultiplayerGameState::AMultiplayerGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	StartingGameTimeInSeconds = 30.0f;
}

float AMultiplayerGameState::GetTimeRemaining()
{
	return StartingGameTimeInSeconds - CurrentGameTimeInSeconds;
}

void AMultiplayerGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentGameTimeInSeconds += DeltaSeconds;
}

void AMultiplayerGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMultiplayerGameState, CurrentGameTimeInSeconds);
}
