// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//A line in the standard form Ax + By + C = 0
//not using this anymore cause I found a better solution ;-;
class AGPASSESSMNT4GROUP17_API FLine
{
public:
	FLine(FVector2D Point1, FVector2D Point2);

	FLine GetPerpendicularLine(FVector2D Point);
	FVector2D GetIntersectionPoint(FLine OtherLine);

private:
	//constructor for perpendicular line
	FLine(float PerpendicularA, float PerpendicularB, FVector2D Point);
	
	float A;
	float B;
	float C;
};
