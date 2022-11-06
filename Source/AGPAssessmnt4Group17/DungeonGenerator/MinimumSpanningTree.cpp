// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimumSpanningTree.h"

FMinimumSpanningTree::FMinimumSpanningTree(TArray<FMyEdge> Edges, TArray<float> Weights)
{
	this->Edges = Edges;
	this->Weights = Weights;
}

TArray<FMyEdge> FMinimumSpanningTree::ConstructTree()
{
	TArray<FMyEdge> Tree;

	SortEdges();

	for(int32 I = 0; I < Edges.Num(); I++)
	{
		if(!DoesEdgeCreateLoop(Edges[I], Tree))
		{
			Tree.Add(Edges[I]);
		}
	}

	return Tree;
}

//uses insertion sort to sort the edges (can be improved later)
void FMinimumSpanningTree::SortEdges()
{
	for(int32 I = 1; I < Edges.Num(); I++)
	{
		float SelectedWeight = Weights[I];
		FMyEdge SelectedEdge = Edges[I];

		int32 J = I - 1;

		while(J >= 0 && SelectedWeight < Weights[J])
		{
			Weights[J + 1] = Weights[J];
			Edges[J + 1] = Edges[J];
			J--;
		}
		Weights[J + 1] = SelectedWeight;
		Edges[J + 1] = SelectedEdge;
	}
}

//lazy, does not use union find
bool FMinimumSpanningTree::DoesEdgeCreateLoop(FMyEdge Edge, TArray<FMyEdge> Tree)
{
	int32 Vertex1Count = 0;
	int32 Vertex2Count = 0;

	for(FMyEdge CurrentEdge : Tree)
	{
		if(CurrentEdge.HasVertex(Edge.Vertex1))
		{
			Vertex1Count++;
		}

		if(CurrentEdge.HasVertex(Edge.Vertex2))
		{
			Vertex2Count++;
		}
	}

	//"good enough"
	return Vertex1Count > 4 || Vertex2Count > 4;
}
