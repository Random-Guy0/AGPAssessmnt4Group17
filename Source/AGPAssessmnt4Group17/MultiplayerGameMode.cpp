// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"

#include "EngineUtils.h"
#include "PlayerHUD.h"
#include "PlayerControls/PlayerCharacter.h"

void AMultiplayerGameMode::Respawn(AController* PlayerToRespawn)
{
	if(PlayerToRespawn)
	{
		//Hide the hud
		APlayerController* PlayerController = Cast<APlayerController>(PlayerToRespawn);
		if (PlayerController)
		{
			APlayerCharacter* Character = Cast<APlayerCharacter>(PlayerController->GetPawn());
			if (Character && !Character->IsLocallyControlled())
			{
				Character->SetPlayerHUDVisibility(false);
			} 
			else if (Character && Character->IsLocallyControlled())
			{
				APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
				if (PlayerHUD)
				{
					PlayerHUD->HideHUD();
				}
			}
		}

		//Remove the player
		APawn* Pawn = PlayerToRespawn->GetPawn();
		if (Pawn)
		{
			Pawn->SetLifeSpan(0.1f);
		}

		//Trigger the respawn process

		FTimerHandle RespawnTimer;
		FTimerDelegate RespawnDelegate;
		RespawnDelegate.BindUFunction(this, TEXT("TriggerRespawn"), PlayerToRespawn);
		GetWorldTimerManager().SetTimer(RespawnTimer, RespawnDelegate, 5.0f, false);
	}
}

void AMultiplayerGameMode::TriggerRespawn(AController* Controller)
{
	if (Controller)
	{
		AActor* SpawnPoint = ChoosePlayerStart(Controller);
		if (SpawnPoint)
		{
			APawn* SpawnedPlayer = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation());
			if (SpawnedPlayer)
			{
				Controller->Possess(SpawnedPlayer);
			}
		}
	}

	//Show the hud
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		APlayerCharacter* Character = Cast<APlayerCharacter>(PlayerController->GetPawn());
		if (Character && !Character->IsLocallyControlled())
		{
			Character->SetPlayerHUDVisibility(true);
		}
		else if (Character && Character->IsLocallyControlled())
		{
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
			if (PlayerHUD)
			{
				PlayerHUD->ShowHUD();
				PlayerHUD->SetPlayerHealthBarPercent(1.0f);
			}
			
			Character->ResetModelVisibility();
		}
	}
}

//custom spawning behaviour, randomly picks location
AActor* AMultiplayerGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if(Player->StartSpot.IsExplicitlyNull() && StartLocations.Num() > 0)
	{
		int32 RandomStart = FMath::RandRange(0, StartLocations.Num() - 1);

		APlayerStart* StartLocation = StartLocations[RandomStart];
		StartLocations.RemoveAt(RandomStart);
		return StartLocation;
	}
	else if(!Player->StartSpot.IsExplicitlyNull())
	{
		int32 RandomStart = FMath::RandRange(0, DungeonManager->PlayerStartLocations.Num() - 1);

		APlayerStart* StartLocation = DungeonManager->PlayerStartLocations[RandomStart];
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
		StartLocations = DungeonManager->PlayerStartLocations;
	}

	Floor = GetWorld()->SpawnActor<AProceduralFloor>(ProceduralFloorBlueprint);
	Floor->SetSizeFloor(DungeonManager->DungeonWidth * DungeonManager->GridSize, DungeonManager->DungeonDepth * DungeonManager->GridSize);
	


}
