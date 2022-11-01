// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "DelaunayTriangulation.h"
#include "DrawDebugHelpers.h"
#include "MinimumSpanningTree.h"
#include "Pathfinding.h"
#include "Engine/StaticMeshActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADungeonManager::ADungeonManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;

	///Set default values
	PerlinThreshold = 0.6f;
	PerlinRoughness = 0.3f;

	DungeonWidth = 75;
	DungeonDepth = 75;

	GridSize = 400.0f;

	RoomHeight = 500.0f;

	MaxRoomWidth = 6;
	MinRoomWidth = 2;

	MaxRoomDepth = 6;
	MinRoomDepth = 3;

	GenerateRandomValues();
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();
	
	//CreateDungeon();
}

// Called every frame
void ADungeonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	if (PlayerStart)
	{
		PlacePlayer();
	}
}

void ADungeonManager::ClearDungeon()
{
	FlushPersistentDebugLines(GetWorld());
	Grid.ClearAllMeshSegments();
}

void ADungeonManager::CreateDungeon()
{
	ClearDungeon();

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
				Grid.AddRoom(FVector2D(I, J), RoomWidths[J * DungeonWidth + I], RoomDepths[J * DungeonWidth + I]);
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

//find all vertices that an edge with the supplied vertex
TArray<FVector2D> ADungeonManager::FindConnectedVertices(FVector2D Vertex, TArray<FMyEdge> Edges)
{
	TArray<FVector2D> ConnectedVertices;
	for (FMyEdge CurrentEdge : Edges)
	{
		if (CurrentEdge.Vertex1.Equals(Vertex))
		{
			ConnectedVertices.Add(CurrentEdge.Vertex2);
		}
		else if (CurrentEdge.Vertex2.Equals(Vertex))
		{
			ConnectedVertices.Add(CurrentEdge.Vertex1);
		}
	}

	return ConnectedVertices;
}

void ADungeonManager::GenerateRandomValues()
{
	PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);

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

	bRegenerateDungeon = true;
}

void ADungeonManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADungeonManager, PerlinOffset);
	DOREPLIFETIME(ADungeonManager, RoomWidths);
	DOREPLIFETIME(ADungeonManager, RoomDepths);
}

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

	TArray<EGridSegment> GridArray = Grid.GetGrid();

	FPathfinding AStar(AllVertices, DungeonWidth, DungeonDepth);

	for (FMyEdge Edge : Tree)
	{
		TArray<FVector2D> Path = AStar.GeneratePath(Edge.Vertex1, Edge.Vertex2);
		Grid.AddHallway(Path);
	}
}

void ADungeonManager::PlacePlayer()
{
	FVector Position = FVector((Grid.GetRandomRoomPosition() + FVector2D(1, 1)) * GridSize,
	                           PlayerStart->GetActorLocation().Z);
	PlayerStart->SetActorLocation(Position);
}

bool ADungeonManager::ShouldTickIfViewportsOnly() const
{
	return true;
}
