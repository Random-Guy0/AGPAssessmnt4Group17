// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationNode.h"

/**
 * 
 */
class AGPASSESSMNT4GROUP17_API FPathfinding
{
public:
	FPathfinding(TArray<FVector2D> Vertices, int32 GridWidth, int32 GridDepth);

	TArray<FVector2D> GeneratePath(FVector2D Start, FVector2D End);

private:
	int32 GridWidth;
	int32 GridDepth;
	
	TArray<FNavigationNode*> AllNodes;

	TArray<FNavigationNode*> GeneratePath(FNavigationNode* StartNode, FNavigationNode* EndNode);

	TArray<FNavigationNode*> ReconstructPath(FNavigationNode* StartNode, FNavigationNode* EndNode);
};
