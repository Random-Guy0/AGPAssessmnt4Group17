// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GridMeshSegment.generated.h"

UCLASS()
class AGPASSESSMNT4GROUP17_API AGridMeshSegment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMeshSegment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* MeshComponent;

	FVector2D Position;

	void SetPosition(FVector2D PositionArg);

	void SetMeshDetails(float GridSizeArg, float RoomHeightArg, bool bGenLeftWallArg, bool bGenRightWallArg, bool bGenTopWallArg, bool bGenBottomWallArg);
	
	void GenerateMesh();

private:
	UPROPERTY(Replicated)
	float GridSize;
	UPROPERTY(Replicated)
	float RoomHeight;
	UPROPERTY(Replicated)
	bool bGenLeftWall;
	UPROPERTY(Replicated)
	bool bGenRightWall;
	UPROPERTY(Replicated)
	bool bGenTopWall;
	UPROPERTY(Replicated)
	bool bGenBottomWall;

	float TorchSpawnChance;
	
	UMaterialInterface* Material;

	TSubclassOf<AActor> TorchBlueprint;

	
	TSubclassOf<AActor> CoffinBlueprint;

	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
