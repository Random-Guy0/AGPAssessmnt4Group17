// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AGPAssessmnt4Group17/MultiplayerGameMode.h"
#include "AGPAssessmnt4Group17/MultiplayerGameState.h"
#include "AGPAssessmnt4Group17/PlayerHUD.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookSensitivity = 1.0f;
	SprintMultiplier = 1.5f;

	SprintMovementSpeed = GetCharacterMovement()->MaxWalkSpeed * SprintMultiplier;
	NormalMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;

	KillCount = 0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Camera = FindComponentByClass<UCameraComponent>();

	USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(GetDefaultSubobjectByName(TEXT("Arms")));

	if (SkeletalMesh) // Make sure the skeletal mesh was found
	{
		AnimInstance = Cast<UFirstPersonAnimInstance>(SkeletalMesh->GetAnimInstance());
	}

	HealthComponent = FindComponentByClass<UHealthComponent>();

	if (HealthComponent)
	{
		HealthComponent->SetIsReplicated(true);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMultiplayerGameState* GameState = GetWorld()->GetGameState<AMultiplayerGameState>();
	if(GetLocalRole() == ROLE_AutonomousProxy && GameState)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
			if (PlayerHUD)
			{
				float TimeRemaining = GameState->GetTimeRemaining();

				if(TimeRemaining <= 0)
				{
					TimeRemaining = 0;
					PlayerHUD->ShowEndScreen(KillCount);
				}
				
				PlayerHUD->SetCountdownText(TimeRemaining);
			}
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::SprintEnd);

	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &APlayerCharacter::Reload);
}

void APlayerCharacter::MoveForward(float Value)
{
	FRotator ForwardRotation = GetControlRotation();
	ForwardRotation.Roll = 0.0f;
	ForwardRotation.Pitch = 0.0f;
	AddMovementInput(ForwardRotation.Vector(), Value);
}

void APlayerCharacter::Strafe(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::LookUp(float Value)
{
	FRotator LookUpRotation = FRotator::ZeroRotator;
	LookUpRotation.Pitch = Value * LookSensitivity;

	if (Camera && abs(Camera->GetRelativeRotation().Pitch + LookUpRotation.Pitch < 90.0f))
	{
		Camera->AddRelativeRotation(LookUpRotation);
		FRotator RelativeRotation = Camera->GetRelativeRotation();
		RelativeRotation.Yaw = 0.0f;
		RelativeRotation.Roll = 0.0f;
		Camera->SetRelativeRotation(RelativeRotation);
	}
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * LookSensitivity);
}

void APlayerCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMovementSpeed;
	ServerSprintStart();

	if (AnimInstance)
	{
		AnimInstance->bIsSprinting = true;
	}
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalMovementSpeed;
	ServerSprintEnd();

	if (AnimInstance)
	{
		AnimInstance->bIsSprinting = false;
	}
}

void APlayerCharacter::Reload()
{
	BlueprintReload();
}

void APlayerCharacter::OnDeath()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		AMultiplayerGameMode* MultiplayerGameMode = Cast<AMultiplayerGameMode>(GetWorld()->GetAuthGameMode());
		if (MultiplayerGameMode)
		{
			MultiplayerGameMode->Respawn(GetController());
		}
	}
}

void APlayerCharacter::UpdateKillCount_Implementation()
{
	++KillCount;
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
		if (PlayerHUD)
		{
			PlayerHUD->SetKillCountText(KillCount);
		}
	}
}

void APlayerCharacter::SetPlayerHUDVisibility_Implementation(bool bHUDVisible)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
			if (PlayerHUD)
			{
				bHUDVisible ? PlayerHUD->ShowHUD() : PlayerHUD->HideHUD();
			}
		}
	}
}

void APlayerCharacter::ServerSprintStart_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMovementSpeed;
}

void APlayerCharacter::ServerSprintEnd_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalMovementSpeed;
}
