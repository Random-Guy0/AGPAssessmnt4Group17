// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

//default constructor
FGrid::FGrid()
{
	FGrid(nullptr, 100, 100, 100.0f);
}

//initialise, setting all required values
FGrid::FGrid(UWorld* World, int32 GridWidth, int32 GridDepth, float GridSize)
{
	this->World = World;
	
	this->GridWidth = GridWidth;
	this->GridDepth = GridDepth;
	this->GridSize = GridSize;

	Grid.SetNum((GridDepth - 1) * GridWidth + GridWidth);
	MeshSegments.SetNum((GridDepth - 1) * GridWidth + GridWidth);
}

//check if an area on the grid is empty
bool FGrid::IsAreaEmpty(FVector2D StartPoint, int32 AreaWidth, int32 AreaDepth)
{
	if(StartPoint.X + AreaWidth > GridWidth || StartPoint.Y + AreaDepth > GridDepth)
	{
		return false;
	}
	
	bool bAreaEmpty = true;

	for(int I = StartPoint.X; I < StartPoint.X + AreaWidth; I++)
	{
		for(int J = StartPoint.Y; J < StartPoint.Y + AreaDepth; J++)
		{
			if(Grid[J * GridWidth + I] != EGridSegment::Empty)
			{
				bAreaEmpty = false;
				break;
			}
		}

		if(!bAreaEmpty)
		{
			break;
		}
	}
	
	return bAreaEmpty;
}

//spawns a mesh segment
AGridMeshSegment* FGrid::AddMeshSegment(FVector2D Position)
{
	if(World)
	{
		AGridMeshSegment* NewGridMeshSegment = World->SpawnActor<AGridMeshSegment>(FVector(Position * GridSize, 0), FRotator::ZeroRotator);
		NewGridMeshSegment->SetPosition(Position);

		MeshSegments[Position.Y * GridWidth + Position.X] = NewGridMeshSegment;

		return NewGridMeshSegment;
	}
	else
	{
		return nullptr;
	}
}

//adds a new room to the grid
void FGrid::AddRoom(FVector2D Position, int32 RoomWidth, int32 RoomDepth)
{
	if(IsAreaEmpty(Position, RoomWidth, RoomDepth))
	{
		TArray<AGridMeshSegment*> CurrentRoomSegments;
		for(int I = Position.X; I < Position.X + RoomWidth; I++)
		{
			for(int J = Position.Y; J < Position.Y + RoomDepth; J++)
			{
				if(World)
				{
					Grid[J * GridWidth + I] = EGridSegment::Room;
					AGridMeshSegment* NewMeshSegment = AddMeshSegment(FVector2D(I, J));
					CurrentRoomSegments.Add(NewMeshSegment);
				}
			}
		}
		Rooms.Add(new FRoom(Position, RoomWidth, RoomDepth, CurrentRoomSegments));
	}
}

//adds a new hallway based of an array of points
void FGrid::AddHallway(TArray<FVector2D> Positions)
{
	for(FVector2D Position : Positions)
	{
		int32 Index = Position.Y * GridWidth + Position.X;
		if(Grid[Index] == EGridSegment::Empty)
		{
			AddMeshSegment(Position);
			Grid[Index] = EGridSegment::Hallway;
		}
	}
}

//generate the mesh for the dungeon
void FGrid::GenerateAllMeshSegments(float RoomHeight)
{
	for(AGridMeshSegment* MeshSegment: MeshSegments)
	{
		if(MeshSegment)
		{
			bool bGenLeftWall = true;
			bool bGenRightWall = true;
			bool bGenTopWall = true;
			bool bGenBottomWall = true;

			int32 IndexToCheck = MeshSegment->Position.Y * GridWidth + (MeshSegment->Position.X - 1);
			if(IndexToCheck >= 0 && IndexToCheck < Grid.Num())
			{
				bGenBottomWall = Grid[IndexToCheck] == EGridSegment::Empty;
			}

			IndexToCheck = MeshSegment->Position.Y * GridWidth + (MeshSegment->Position.X + 1);
			if(IndexToCheck >= 0 && IndexToCheck < Grid.Num())
			{
				bGenTopWall = Grid[IndexToCheck] == EGridSegment::Empty;
			}

			IndexToCheck = (MeshSegment->Position.Y + 1) * GridWidth + MeshSegment->Position.X;
			if(IndexToCheck >= 0 && IndexToCheck < Grid.Num())
			{
				bGenRightWall = Grid[IndexToCheck] == EGridSegment::Empty;
			}

			IndexToCheck = (MeshSegment->Position.Y - 1) * GridWidth + MeshSegment->Position.X;
			if(IndexToCheck >= 0 && IndexToCheck < Grid.Num())
			{
				bGenLeftWall = Grid[IndexToCheck] == EGridSegment::Empty;
			}
			
			MeshSegment->SetMeshDetails(GridSize, RoomHeight, bGenLeftWall, bGenRightWall, bGenTopWall, bGenBottomWall);
			//MeshSegment->GenerateMesh();
		}
	}
}

//remove the mesh for the dungeon
void FGrid::ClearAllMeshSegments()
{
	for(AGridMeshSegment* MeshSegment : MeshSegments)
	{
		if(MeshSegment)
			MeshSegment->Destroy();
	}

	MeshSegments = TArray<AGridMeshSegment*>();
	MeshSegments.SetNum((GridDepth - 1) * GridWidth + GridWidth);

	Grid = TArray<EGridSegment>();
	Grid.SetNum((GridDepth - 1) * GridWidth + GridWidth);

	for(int32 I = 0; I < Grid.Num(); I++)
	{
		Grid[I] = EGridSegment::Empty;
	}

	Rooms.Empty();
}

//get an array of all the rooms
TArray<FRoom*> FGrid::GetRooms()
{
	return Rooms;
}

//returns the grid itself
TArray<EGridSegment> FGrid::GetGrid()
{
	return Grid;
}

//remove a room at the specified index
void FGrid::RemoveRoom(int32 Index)
{
	FRoom* RoomToRemove = Rooms[Index];
	Rooms.RemoveAt(Index);

	for(int32 I = MeshSegments.Num() - 1; I >= 0; I--)
	{
		if(RoomToRemove->HasMeshSegment(MeshSegments[I]))
		{
			Grid[I] = EGridSegment::Empty;
			MeshSegments[I]->Destroy();
			MeshSegments.RemoveAt(I);
		}
	}

	delete RoomToRemove;
}

//returns a list of all currently empty points
TArray<FVector2D> FGrid::GetEmptyPoints()
{
	TArray<FVector2D> EmptyPoints;
	EmptyPoints.SetNum(Grid.Num());
	
	for(int32 I = 0; I < GridWidth; I++)
	{
		for(int32 J = 0; J < GridDepth; J++)
		{
			if(Grid[J * GridWidth + I] == EGridSegment::Empty)
			{
				EmptyPoints[J * GridWidth + I] = FVector2D(I, J);
			}
			else
			{
				EmptyPoints[J * GridWidth + I] = FVector2D(-1, -1);
			}
		}
	}
	
	return EmptyPoints;
}

//finds the room located at the specified position
FRoom* FGrid::FindRoomAtPosition(FVector2D Position)
{
	FRoom* RoomToReturn = nullptr;

	for(FRoom* Room : Rooms)
	{
		if(Room->Position.Equals(Position))
		{
			RoomToReturn = Room;
			break;
		}
	}

	return RoomToReturn;
}
