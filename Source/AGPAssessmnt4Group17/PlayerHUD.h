// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class AGPASSESSMNT4GROUP17_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	APlayerHUD();

	void SetPlayerHealthBarPercent(float Percent);
	
	void HideHUD();
	void ShowHUD();
	
	UFUNCTION(BlueprintCallable)
	void SetAmmoText(int32 RoundsRemaining, int32 RoundsInMagazine);

	void SetKillCountText(int32 KillCount);

	void SetCountdownText(float TimeRemaining);
	
	void ShowEndScreen(int32 KillCount);

protected:
	virtual void BeginPlay() override;
	
private:
	TSubclassOf<UUserWidget> PlayerHUDClass;
	TSubclassOf<UUserWidget> EndScreenClass;
	UUserWidget* CurrentPlayerHUDWidget;
	UUserWidget* EndScreenWidget;

	UProgressBar* HealthProgressBar;

	class UTextBlock* RoundsInMagazineText;
	UTextBlock* RoundsRemainingText;

	UTextBlock* KillCountText;

	UTextBlock* CountdownText;
};
