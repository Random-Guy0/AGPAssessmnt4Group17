// Fill out your copyright notice in the Description page of Project Settings.


#include "DelaunayTriangulation.h"

FDelaunayTriangulation::FDelaunayTriangulation(TArray<FVector2D> Vertices)
{
	this->Vertices = Vertices;
	
	SuperTriangle = GenerateSuperTriangle();
	Triangulate();
}

//Create a large triangle that surrounds all vertices
FMyTriangle FDelaunayTriangulation::GenerateSuperTriangle()
{
	float MinX = TNumericLimits<float>::Max();
	float MinY = TNumericLimits<float>::Max();
	float MaxX = TNumericLimits<float>::Min();
	float MaxY = TNumericLimits<float>::Min();

	for(FVector2D Vertex : Vertices)
	{
		MinX = FMath::Min(MinX, Vertex.X);
		MinY = FMath::Min(MinY, Vertex.Y);
		MaxX = FMath::Max(MaxX, Vertex.X);
		MaxY = FMath::Max(MaxY, Vertex.Y);
	}

	float DeltaX = (MaxX - MinX);
	float DeltaY = (MaxY - MinY);

	//this triangle will be big enough to include all vertices
	FVector2D Vertex1 = FVector2D(MinX - DeltaX, MinY - DeltaY * 3);
	FVector2D Vertex2 = FVector2D(MinX - DeltaX, MaxY + DeltaY);
	FVector2D Vertex3 = FVector2D(MaxX + DeltaX * 3, MaxY + DeltaY);
	
	return FMyTriangle(Vertex1, Vertex2, Vertex3);
}

//create the triangulation mesh
void FDelaunayTriangulation::Triangulate()
{
	Triangles.Add(SuperTriangle);

	for(FVector2D Vertex : Vertices)
	{
		AddVertex(Vertex);
	}

	RemoveSuperTriangle();

}

//generate triangles for each vertex
void FDelaunayTriangulation::AddVertex(FVector2D Vertex)
{
	TArray<FMyEdge> Edges;
	
	TArray<int32> TrianglesToRemove;
	for(int i = 0; i < Triangles.Num(); i++)
	{
		if(Triangles[i].IsInCircumcircle(Vertex))
		{
			TrianglesToRemove.Add(i);
			Edges.Add(FMyEdge(Triangles[i].Vertex1, Triangles[i].Vertex2));
			Edges.Add(FMyEdge(Triangles[i].Vertex2, Triangles[i].Vertex3));
			Edges.Add(FMyEdge(Triangles[i].Vertex3, Triangles[i].Vertex1));
		}
	}

	Edges = UniqueEdges(Edges);

	for(int i = TrianglesToRemove.Num() - 1; i >= 0; i--)
	{
		Triangles.RemoveAt(TrianglesToRemove[i]);
	}

	for(FMyEdge CurrentEdge : Edges)
	{
		Triangles.Add(FMyTriangle(CurrentEdge.Vertex1, CurrentEdge.Vertex2, Vertex));
	}
}

//remove duplicate edges
TArray<FMyEdge> FDelaunayTriangulation::UniqueEdges(TArray<FMyEdge> Edges)
{
	TArray<FMyEdge> UniqueEdges;

	for(int i = 0; i < Edges.Num(); i++)
	{
		bool bIsUnique = true;

		for(int j = 0; j < Edges.Num(); j++)
		{
			if(i != j && Edges[i].Equals(Edges[j]))
			{
				bIsUnique = false;
				break;
			}
		}

		if(bIsUnique)
		{
			UniqueEdges.Add(Edges[i]);
		}
	}

	return  UniqueEdges;
}

//remove the original super triangle and all connected edges
void FDelaunayTriangulation::RemoveSuperTriangle()
{
	for(int i = Triangles.Num() - 1; i >= 0; i--)
	{
		if(Triangles[i].HasVertex(SuperTriangle.Vertex1) || Triangles[i].HasVertex(SuperTriangle.Vertex2) || Triangles[i].HasVertex(SuperTriangle.Vertex3))
		{
			Triangles.RemoveAt(i);
		}
	}
}