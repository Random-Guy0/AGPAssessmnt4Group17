// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEdge.h"

/**
 * 
 */
class AGPASSESSMNT4GROUP17_API FMinimumSpanningTree
{
public:
	FMinimumSpanningTree(TArray<FMyEdge> Edges, TArray<float> Weights);

	TArray<FMyEdge> ConstructTree();

private:
	TArray<FMyEdge> Edges;
	TArray<float> Weights;

	void SortEdges();
	bool DoesEdgeCreateLoop(FMyEdge Edge, TArray<FMyEdge> Tree);
};
