// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridMeshSegment.h"

/**
 * 
 */
class AGPASSESSMNT4GROUP17_API FRoom
{
public:
	FRoom(FVector2D Position, int32 Width, int32 Depth, TArray<AGridMeshSegment*> MeshSegments);

	FVector2D Position;

	int32 Width;
	int32 Depth;

	FVector2D GetClosestMeshSegmentPosition(FVector2D OtherPosition);

	bool HasMeshSegment(AGridMeshSegment* OtherMeshSegment);

private:
	TArray<AGridMeshSegment*> MeshSegments;
	
};
