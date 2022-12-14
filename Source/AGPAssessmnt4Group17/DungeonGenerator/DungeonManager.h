// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelaunayTriangulation.h"
#include "Grid.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "DungeonManager.generated.h"

UCLASS()
class AGPASSESSMNT4GROUP17_API ADungeonManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	float PerlinThreshold;
	
	UPROPERTY(EditAnywhere)
	float PerlinRoughness;

	UPROPERTY(EditAnywhere)
	int32 DungeonWidth;

	UPROPERTY(EditAnywhere)
	int32 DungeonDepth;

	UPROPERTY(EditAnywhere)
	float GridSize;

	UPROPERTY(EditAnywhere)
	float Floor;

	FGrid Grid;

	UPROPERTY(EditAnywhere)
	float RoomHeight;
	
	UPROPERTY(EditAnywhere)
	int32 MinRoomWidth;
	UPROPERTY(EditAnywhere)
	int32 MaxRoomWidth;
	
	UPROPERTY(EditAnywhere)
	int32 MinRoomDepth;
	UPROPERTY(EditAnywhere)
	int32 MaxRoomDepth;

	TArray<APlayerStart*> PlayerStartLocations;
	
	void CreateDungeon();

	void GenerateRandomValues();
	
	void GenerateRooms();
	void ClearDungeon();

	FDelaunayTriangulation ComputeDelaunayTriangulation();
	TArray<FMyEdge> ConstructTree(FDelaunayTriangulation Triangulation);
	void AStarHallwayGeneration(TArray<FMyEdge> Tree);

	void PlacePlayers();
	
	void GenerateDungeon();

	UPROPERTY(EditAnywhere)
	bool bDebugDelaunayTriangulation;

	UPROPERTY(EditAnywhere)
	bool bDebugTree;

	UPROPERTY(EditAnywhere)
	bool bRegenerateDungeon;

	UPROPERTY(EditAnywhere)
	bool bClearDungeon;

	void DebugDelaunayTriangulation(FDelaunayTriangulation Triangulation);
	void DebugTree(TArray<FMyEdge> Tree);

	virtual bool ShouldTickIfViewportsOnly() const override;

private:
	float PerlinOffset;
	
	TArray<int32> RoomWidths;
	TArray<int32> RoomDepths;
};
