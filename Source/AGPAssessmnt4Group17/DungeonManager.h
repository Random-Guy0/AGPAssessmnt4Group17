// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelaunayTriangulation.h"
#include "Grid.h"
#include "HallwaySegment.h"
#include "GameFramework/Actor.h"
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
	AActor* PlayerStart;
	
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
	
	TArray<AHallwaySegment*> HallwaySegments;
	
	void CreateDungeon();
	
	void GenerateRooms();
	void ClearDungeon();

	FDelaunayTriangulation ComputeDelaunayTriangulation();
	TArray<FMyEdge> ConstructTree(FDelaunayTriangulation Triangulation);
	void AStarHallwayGeneration(TArray<FMyEdge> Tree);

	void PlacePlayer();
	
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
	UPROPERTY(Replicated)
	float PerlinOffset;

	UPROPERTY(Replicated)
	TArray<int32> RoomWidths;
	UPROPERTY(Replicated)
	TArray<int32> RoomDepths;
	
	TArray<FVector2D> FindConnectedVertices(FVector2D Vertex, TArray<FMyEdge> Edges);
	
	void GenerateRandomValues();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
