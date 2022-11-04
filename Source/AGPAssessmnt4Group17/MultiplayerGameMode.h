// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonManager.h"
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
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	ADungeonManager* DungeonManager;

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override; 
};
