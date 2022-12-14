// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

FRoom::FRoom(FVector2D Position, int32 Width, int32 Depth, TArray<AGridMeshSegment*> MeshSegments)
{
	this->Position = Position;
	this->Width = Width;
	this->Depth = Depth;
	this->MeshSegments = MeshSegments;
}

FVector2D FRoom::GetClosestMeshSegmentPosition(FVector2D OtherPosition)
{
	FVector2D ClosestPos;

	if(MeshSegments.Num() > 0)
		ClosestPos = MeshSegments[0]->Position;

	for(int I = 1; I < MeshSegments.Num(); I++)
	{
		FVector2D MeshSegmentPos2D = MeshSegments[I]->Position;
		if(FVector2D::Distance(OtherPosition, MeshSegmentPos2D) < FVector2D::Distance(OtherPosition, ClosestPos))
		{
			ClosestPos = MeshSegmentPos2D;
		}
	}

	return ClosestPos;
}

bool FRoom::HasMeshSegment(AGridMeshSegment* OtherMeshSegment)
{
	bool bHasMeshSegment = false;
	for(AGridMeshSegment* MeshSegment : MeshSegments)
	{
		if(MeshSegment == OtherMeshSegment)
		{
			bHasMeshSegment = true;
			break;
		}
	}

	return bHasMeshSegment;
}
