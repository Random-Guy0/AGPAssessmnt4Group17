// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MultiplayerGameState.generated.h"

/**
 * 
 */
UCLASS()
class AGPASSESSMNT4GROUP17_API AMultiplayerGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMultiplayerGameState();

	UPROPERTY(EditAnywhere)
	float StartingGameTimeInSeconds;
	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentGameTimeInSeconds;

	float GetTimeRemaining();

	virtual void Tick(float DeltaSeconds) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
