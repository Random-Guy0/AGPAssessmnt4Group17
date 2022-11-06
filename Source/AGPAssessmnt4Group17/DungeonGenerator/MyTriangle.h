// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//holds a triangle used for Delaunay Triangulation
class AGPASSESSMNT4GROUP17_API FMyTriangle
{
	//inteternal circumcircle class
	class FCircumcircle
	{
		public:
			FCircumcircle(FVector2D Vertex1, FVector2D Vertex2, FVector2D Vertex3);
	
			FVector2D Center;
			float Radius;

			bool IsInCircumcircle(FVector2D Vertex);
	};
	
public:
	FMyTriangle();
	FMyTriangle(FVector2D Vertex1, FVector2D Vertex2, FVector2D Vertex3);

	FVector2D Vertex1;
	FVector2D Vertex2;
	FVector2D Vertex3;

	FCircumcircle Circumcircle;

	bool IsInCircumcircle(FVector2D Vertex);
	bool HasVertex(FVector2D Vertex);
};
