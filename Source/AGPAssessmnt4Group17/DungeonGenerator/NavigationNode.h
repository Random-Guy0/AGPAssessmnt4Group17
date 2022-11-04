// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class AGPASSESSMNT4GROUP17_API FNavigationNode
{
public:
	FNavigationNode(FVector2D Position);
	
	FVector2D Position;
	
	float GScore;
	float HScore;

	TArray<FNavigationNode*> ConnectedNodes;

	FNavigationNode* CameFrom;

	float FScore();
};
