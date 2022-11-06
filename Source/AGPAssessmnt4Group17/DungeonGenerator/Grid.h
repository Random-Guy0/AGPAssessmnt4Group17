// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridMeshSegment.h"
#include "Room.h"

UENUM()
enum class EGridSegment : uint8
{
	Empty,
	Room,
	Hallway
};

class AGPASSESSMNT4GROUP17_API FGrid
{
public:
	FGrid();
	FGrid(UWorld* World, int32 GridWidth, int32 GridDepth, float GridSize);

	bool IsAreaEmpty(FVector2D StartPoint, int32 AreaWidth, int32 AreaDepth);

	AGridMeshSegment* AddMeshSegment(FVector2D Position);
	void AddRoom(FVector2D Position, int32 RoomWidth, int32 RoomDepth);
	void AddHallway(TArray<FVector2D> Positions);

	void GenerateAllMeshSegments(float RoomHeight);
	void ClearAllMeshSegments();

	TArray<FRoom*> GetRooms();
	TArray<EGridSegment> GetGrid();

	void RemoveRoom(int32 Index);

	TArray<FVector2D> GetEmptyPoints();

	FRoom* FindRoomAtPosition(FVector2D Position);

private:
	UWorld* World;
	
	int32 GridWidth;
	int32 GridDepth;
	float GridSize;
	
	TArray<EGridSegment> Grid;
	TArray<AGridMeshSegment*> MeshSegments;
	TArray<FRoom*> Rooms;
	
};
