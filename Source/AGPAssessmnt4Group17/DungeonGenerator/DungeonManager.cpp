// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "DelaunayTriangulation.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "MinimumSpanningTree.h"
#include "Pathfinding.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADungeonManager::ADungeonManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///Set default values
	PerlinThreshold = 0.6f;
	PerlinRoughness = 0.3f;

	DungeonWidth = 50;
	DungeonDepth = 50;

	GridSize = 400.0f;

	RoomHeight = 500.0f;

	MaxRoomWidth = 6;
	MinRoomWidth = 2;

	MaxRoomDepth = 6;
	MinRoomDepth = 3;
}

// Called when the game starts or when spawned
void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADungeonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//intended for testing in the editor
	if (bRegenerateDungeon)
	{
		bRegenerateDungeon = false;

		CreateDungeon();
	}

	if (bClearDungeon)
	{
		bClearDungeon = false;

		ClearDungeon();
	}
}

//Generates the dungeon
void ADungeonManager::GenerateDungeon()
{
	Grid = FGrid(GetWorld(), DungeonWidth, DungeonDepth, GridSize);
	GenerateRooms();

	FDelaunayTriangulation Triangulation = ComputeDelaunayTriangulation();
	TArray<FMyEdge> Tree = ConstructTree(Triangulation);
	AStarHallwayGeneration(Tree);

	Grid.GenerateAllMeshSegments(RoomHeight);
	PlacePlayers();
}

//clears the dungeon, meant for testing in editor
void ADungeonManager::ClearDungeon()
{
	FlushPersistentDebugLines(GetWorld());
	Grid.ClearAllMeshSegments();
}

//generate the dungeon with a separate random values function
void ADungeonManager::CreateDungeon()
{
	ClearDungeon();

	GenerateRandomValues();

	GenerateDungeon();
}

//use perlin noise to randomly place rooms
void ADungeonManager::GenerateRooms()
{
	for (int32 I = 0; I < DungeonWidth; I++)
	{
		for (int32 J = 0; J < DungeonDepth; J++)
		{
			float PerlinValue = FMath::PerlinNoise2D(FVector2D(I * PerlinRoughness + PerlinOffset,
			                                                   J * PerlinThreshold + PerlinOffset));

			//only create a room if the value returned by the perlin noise function exceed a set value
			if (PerlinValue >= PerlinThreshold)
			{
				Grid.AddRoom(FVector2D(I, J), RoomWidths[J * DungeonWidth + I],
					RoomDepths[J * DungeonWidth + I]);
			}
		}
	}
}

//create a triangular mesh using Delaunay Triangulation to connect the rooms
FDelaunayTriangulation ADungeonManager::ComputeDelaunayTriangulation()
{
	//create a list of vertices to pass to the triangulation function
	TArray<FVector2D> Vertices;
	for (FRoom* Room : Grid.GetRooms())
	{
		Vertices.Add(Room->Position);
	}
	FDelaunayTriangulation Triangulation = FDelaunayTriangulation(Vertices);

	if (bDebugDelaunayTriangulation)
	{
		DebugDelaunayTriangulation(Triangulation);
	}
	return Triangulation;
}

//draw debug lines to debug the triangulation mesh
void ADungeonManager::DebugDelaunayTriangulation(FDelaunayTriangulation Triangulation)
{
	for (FMyTriangle CurrentTriangle : Triangulation.Triangles)
	{
		DrawDebugLine(GetWorld(), FVector(CurrentTriangle.Vertex1, 0) * GridSize,
		              FVector(CurrentTriangle.Vertex2, 0) * GridSize, FColor::Red, true, -1, 0, 50);
		DrawDebugLine(GetWorld(), FVector(CurrentTriangle.Vertex2, 0) * GridSize,
		              FVector(CurrentTriangle.Vertex3, 0) * GridSize, FColor::Red, true, -1, 0, 50);
		DrawDebugLine(GetWorld(), FVector(CurrentTriangle.Vertex3, 0) * GridSize,
		              FVector(CurrentTriangle.Vertex1, 0) * GridSize, FColor::Red, true, -1, 0, 50);
	}
}

//construct a tree-like structure from the triangulation mesh
//this reduces the amount of loops/triangles found in the mesh
TArray<FMyEdge> ADungeonManager::ConstructTree(FDelaunayTriangulation Triangulation)
{
	//get edges from triangles
	TArray<FMyEdge> Edges;
	for (FMyTriangle CurrentTriangle : Triangulation.Triangles)
	{
		Edges.Add(FMyEdge(CurrentTriangle.Vertex1, CurrentTriangle.Vertex2));
		Edges.Add(FMyEdge(CurrentTriangle.Vertex2, CurrentTriangle.Vertex3));
		Edges.Add(FMyEdge(CurrentTriangle.Vertex3, CurrentTriangle.Vertex1));
	}

	//assign weights to the edges
	TArray<float> Weights;
	for (FMyEdge Edge : Edges)
	{
		Weights.Add(Edge.Distance());
	}

	FMinimumSpanningTree MinimumSpanningTree(Edges, Weights);

	TArray<FMyEdge> Tree = MinimumSpanningTree.ConstructTree();

	//some rooms are not connect, remove them
	for (int32 I = Grid.GetRooms().Num() - 1; I >= 0; I--)
	{
		bool bIsInTree = false;
		for (FMyEdge Edge : Tree)
		{
			if (Edge.HasVertex(Grid.GetRooms()[I]->Position))
			{
				bIsInTree = true;
				break;
			}
		}

		if (!bIsInTree)
		{
			Grid.RemoveRoom(I);
		}
	}

	if (bDebugTree)
	{
		DebugTree(Tree);
	}

	return Tree;
}

//generate the random values needed to generate the rooms
void ADungeonManager::GenerateRandomValues()
{
	PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);

	//the width and depth are generated for each point a room could potentially be created at
	RoomWidths = TArray<int32>();
	RoomWidths.SetNum((DungeonDepth - 1) * DungeonWidth + DungeonWidth);
	RoomDepths = TArray<int32>();
	RoomDepths.SetNum((DungeonDepth - 1) * DungeonWidth + DungeonWidth);

	for (int32 I = 0; I < RoomWidths.Num(); I++)
	{
		RoomWidths[I] = FMath::RandRange(MinRoomWidth, MaxRoomWidth);
	}

	for (int32 I = 0; I < RoomDepths.Num(); I++)
	{
		RoomDepths[I] = FMath::RandRange(MinRoomDepth, MaxRoomDepth);
	}
}

//draw debug lines to debug the tree
void ADungeonManager::DebugTree(TArray<FMyEdge> Tree)
{
	for (FMyEdge CurrentEdge : Tree)
	{
		DrawDebugLine(GetWorld(), FVector(CurrentEdge.Vertex1, 0) * GridSize,
		              FVector(CurrentEdge.Vertex2, 0) * GridSize, FColor::Blue, true, -1, 0, 50);
	}
}

//Generate hallways using A* Pathfinding
void ADungeonManager::AStarHallwayGeneration(TArray<FMyEdge> Tree)
{
	TArray<FVector2D> AllVertices = Grid.GetEmptyPoints();

	//move the points of the edge closer together
	for (FMyEdge Edge : Tree)
	{
		FRoom* Room1 = Grid.FindRoomAtPosition(Edge.Vertex1);
		FRoom* Room2 = Grid.FindRoomAtPosition(Edge.Vertex2);

		if (Room1 && Room2)
		{
			Edge.Vertex1 = Room1->GetClosestMeshSegmentPosition(Room2->Position);
			Edge.Vertex2 = Room2->GetClosestMeshSegmentPosition(Room1->Position);
		}
	}

	//initialise pathfinding
	FPathfinding AStar(AllVertices, DungeonWidth, DungeonDepth);

	//pathfind each edge and add the resulting hallway to the grid
	for (FMyEdge Edge : Tree)
	{
		TArray<FVector2D> Path = AStar.GeneratePath(Edge.Vertex1, Edge.Vertex2);
		Grid.AddHallway(Path);
	}
}

//generate a potential player spawn point in each room
void ADungeonManager::PlacePlayers()
{
	for (int32 I = 0; I < Grid.GetRooms().Num(); I++)
	{
		FVector Position = FVector((Grid.GetRooms()[I]->Position + FVector2D(1, 1)) * GridSize,
		                           90);
		PlayerStartLocations.Add(GetWorld()->SpawnActor<APlayerStart>(Position, FRotator::ZeroRotator));
	}
}

bool ADungeonManager::ShouldTickIfViewportsOnly() const
{
	return true;
}
