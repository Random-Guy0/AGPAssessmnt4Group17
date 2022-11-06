// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDObject (TEXT("/Game/Widgets/PlayerHUDWidget"));
	PlayerHUDClass = PlayerHUDObject.Class;

	if(PlayerHUDClass)
	{
		CurrentPlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if(CurrentPlayerHUDWidget)
		{
			CurrentPlayerHUDWidget->AddToViewport();
			HealthProgressBar = Cast<UProgressBar>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("ProgHealthBar")));

			RoundsRemainingText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("RoundsRemaining")));
			RoundsInMagazineText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("RoundsInMagazine")));
			
			KillCountText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("KillCountText")));
		}
	}
}

void APlayerHUD::SetPlayerHealthBarPercent(float Percent)
{
	if(HealthProgressBar)
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
	if(KillCountText)
	{
		KillCountText->SetText(FText::FromString(FString::Printf(TEXT("%i kills"), KillCount)));
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}
