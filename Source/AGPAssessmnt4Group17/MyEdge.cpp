// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEdge.h"

FMyEdge::FMyEdge(FVector2D Vertex1, FVector2D Vertex2)
{
	this->Vertex1 = Vertex1;
	this->Vertex2 = Vertex2;
}

bool FMyEdge::Equals(FMyEdge OtherEdge)
{
	return (Vertex1.Equals(OtherEdge.Vertex1) && Vertex2.Equals(OtherEdge.Vertex2)) || (Vertex1.Equals(OtherEdge.Vertex2) && Vertex2.Equals(OtherEdge.Vertex1));
}

float FMyEdge::Distance()
{
	return FVector2D::Distance(Vertex1, Vertex2);
}

bool FMyEdge::HasVertex(FVector2D Vertex)
{
	return Vertex1.Equals(Vertex) || Vertex2.Equals(Vertex);
}
