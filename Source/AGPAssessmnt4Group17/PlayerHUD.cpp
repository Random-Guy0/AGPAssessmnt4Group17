// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "MultiplayerGameState.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDObject(TEXT("/Game/Widgets/PlayerHUDWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> EndScreenObject(TEXT("/Game/Main_Menu/GameOver_Widget"));
	PlayerHUDClass = PlayerHUDObject.Class;
	EndScreenClass = EndScreenObject.Class;

	if (PlayerHUDClass)
	{
		CurrentPlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentPlayerHUDWidget)
		{
			CurrentPlayerHUDWidget->AddToViewport();
			HealthProgressBar = Cast<UProgressBar>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("ProgHealthBar")));

			RoundsRemainingText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("RoundsRemaining")));
			RoundsInMagazineText = Cast<
				UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("RoundsInMagazine")));

			KillCountText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("KillCountText")));

			CountdownText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("CountdownText")));
		}
	}
}

void APlayerHUD::SetPlayerHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void APlayerHUD::HideHUD()
{
	if (CurrentPlayerHUDWidget)
	{
		CurrentPlayerHUDWidget->RemoveFromViewport();
	}
}

void APlayerHUD::ShowHUD()
{
	if (CurrentPlayerHUDWidget)
	{
		CurrentPlayerHUDWidget->AddToViewport();
	}
}

void APlayerHUD::SetAmmoText(int32 RoundsRemaining, int32 RoundsInMagazine)
{
	if (RoundsRemainingText && RoundsInMagazineText)
	{
		RoundsRemainingText->SetText(FText::FromString(FString::Printf(TEXT("%i"), RoundsRemaining)));
		RoundsInMagazineText->SetText(FText::FromString(FString::Printf(TEXT("%i"), RoundsInMagazine)));
	}
}

void APlayerHUD::SetKillCountText(int32 KillCount)
{
	if (KillCountText)
	{
		KillCountText->SetText(FText::FromString(FString::Printf(TEXT("%i kills"), KillCount)));
	}
}

void APlayerHUD::SetCountdownText(float TimeRemaining)
{
	int32 Minutes = FMath::Floor(TimeRemaining / 60.0f);
	int32 Seconds = FMath::Floor(TimeRemaining - (Minutes * 60));

	if (CountdownText)
	{
		CountdownText->SetText(FText::FromString(FString::Printf(TEXT("%i:%i"), Minutes, Seconds)));
	}
}

void APlayerHUD::ShowEndScreen(int32 KillCount)
{
	if(!EndScreenWidget && EndScreenClass)
	{
		EndScreenWidget = CreateWidget<UUserWidget>(GetWorld(), EndScreenClass);

		if(EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();
			GetOwningPlayerController()->SetShowMouseCursor(true);

			UTextBlock* FinalScoreText = Cast<UTextBlock>(EndScreenWidget->GetWidgetFromName(TEXT("FinalScoreText")));
			if(FinalScoreText)
			{
				FinalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Final Score: %i kills"), KillCount)));
			}
		}
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}
