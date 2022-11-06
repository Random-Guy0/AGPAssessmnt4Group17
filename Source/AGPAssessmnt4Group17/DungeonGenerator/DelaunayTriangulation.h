// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEdge.h"
#include "MyTriangle.h"

/**
 * 
 */

class AGPASSESSMNT4GROUP17_API FDelaunayTriangulation
{
public:
	FDelaunayTriangulation(TArray<FVector2D> Vertices);

	TArray<FMyTriangle> Triangles;

private:
	TArray<FVector2D> Vertices;
	UWorld* World;

	FMyTriangle SuperTriangle;
	
	FMyTriangle GenerateSuperTriangle();
	void Triangulate();
	void AddVertex(FVector2D Vertex);

	TArray<FMyEdge> UniqueEdges(TArray<FMyEdge> Edges);

	void RemoveSuperTriangle();
};



