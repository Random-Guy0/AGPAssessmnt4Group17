// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonGenerator/DungeonManager.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AGPASSESSMNT4GROUP17_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void Respawn(AController* PlayerToRespawn);
	UFUNCTION()
	void TriggerRespawn(AController* Controller);
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	ADungeonManager* DungeonManager;

	TArray<APlayerStart*> StartLocations;
	
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override; 
};
