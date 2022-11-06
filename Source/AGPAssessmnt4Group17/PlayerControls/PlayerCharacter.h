// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstPersonAnimInstance.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AGPASSESSMNT4GROUP17_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UHealthComponent* HealthComponent;

	int32 KillCount;

	void MoveForward(float Value);
	void Strafe(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	void SprintStart();
	void SprintEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintReload();
	void Reload();

	UFUNCTION(Server, Reliable)
	void ServerSprintStart();
	UFUNCTION(Server, Reliable)
	void ServerSprintEnd();

	void OnDeath();

	UFUNCTION(Client, Reliable)
	void SetPlayerHUDVisibility(bool bHUDVisible);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResetModelVisibility();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void UpdateKillCount();

protected:
	float SprintMovementSpeed;
	float NormalMovementSpeed;

private:
	UPROPERTY(EditAnywhere)
	float LookSensitivity;

	UPROPERTY(EditInstanceOnly)
	float SprintMultiplier;

	UCameraComponent* Camera;
	UFirstPersonAnimInstance* AnimInstance;
};
