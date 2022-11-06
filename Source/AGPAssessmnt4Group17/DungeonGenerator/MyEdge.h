// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AGPASSESSMNT4GROUP17_API FMyEdge
{
public:
	FMyEdge(FVector2D Vertex1, FVector2D Vertex2);
	
	FVector2D Vertex1;
	FVector2D Vertex2;
	
	bool Equals(FMyEdge OtherEdge);

	float Distance();

	bool HasVertex(FVector2D Vertex);
};
