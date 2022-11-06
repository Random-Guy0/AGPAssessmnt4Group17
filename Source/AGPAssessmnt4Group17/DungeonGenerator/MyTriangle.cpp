// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriangle.h"

#include "Line.h"

FMyTriangle::FMyTriangle() : Circumcircle(FVector2D::ZeroVector, FVector2D::ZeroVector, FVector2D::ZeroVector)
{
	this->Vertex1 = FVector2D::ZeroVector;
	this->Vertex2 = FVector2D::ZeroVector;
	this->Vertex3 = FVector2D::ZeroVector;
}

FMyTriangle::FMyTriangle(FVector2D Vertex1, FVector2D Vertex2, FVector2D Vertex3) : Circumcircle(Vertex1, Vertex2, Vertex3)
{
	this->Vertex1 = Vertex1;
	this->Vertex2 = Vertex2;
	this->Vertex3 = Vertex3;
}

bool FMyTriangle::IsInCircumcircle(FVector2D Vertex)
{
	return Circumcircle.IsInCircumcircle(Vertex);
}

bool FMyTriangle::HasVertex(FVector2D Vertex)
{
	return Vertex.Equals(Vertex1) || Vertex.Equals(Vertex2) || Vertex.Equals(Vertex3);
}

//calculates circumcirlce using formula
FMyTriangle::FCircumcircle::FCircumcircle(FVector2D Vertex1, FVector2D Vertex2, FVector2D Vertex3)
{
	float Length1 = FVector2D::Distance(Vertex1, Vertex2);
	float Length2 = FVector2D::Distance(Vertex2, Vertex3);
	float Length3 = FVector2D::Distance(Vertex3, Vertex1);

	float Angle1 = FMath::Acos((FMath::Square(Length1) + FMath::Square(Length3) - FMath::Square(Length2)) / (2 * Length1 * Length3));
	float Angle2 = FMath::Acos((FMath::Square(Length2) + FMath::Square(Length1) - FMath::Square(Length3)) / (2 * Length2 * Length1));
	float Angle3 = FMath::Acos((FMath::Square(Length2) + FMath::Square(Length3) - FMath::Square(Length1)) / (2 * Length2 * Length3));

	float CenterX = (Vertex1.X * FMath::Sin(2 * Angle1) + Vertex2.X * FMath::Sin(2 * Angle2) + Vertex3.X * FMath::Sin(2 * Angle3)) /
		(FMath::Sin(2 * Angle1) + FMath::Sin(2 * Angle2) + FMath::Sin(2 * Angle3));
	float CenterY = (Vertex1.Y * FMath::Sin(2 * Angle1) + Vertex2.Y * FMath::Sin(2 * Angle2) + Vertex3.Y * FMath::Sin(2 * Angle3)) /
		(FMath::Sin(2 * Angle1) + FMath::Sin(2 * Angle2) + FMath::Sin(2 * Angle3));

	Center = FVector2D(CenterX, CenterY);

    float S = (Length1 + Length2 + Length3) / 2.0f;
	float Area = FMath::Sqrt(S * (S - Length1) * (S - Length2) * (S - Length3));

	Radius = (Length1 * Length2 * Length3) / (4.0f * Area);
}

bool FMyTriangle::FCircumcircle::IsInCircumcircle(FVector2D Vertex)
{
	float DistanceX = Vertex.X - Center.X;
	float DistanceY = Vertex.Y - Center.Y;

	float DistanceSquare = (DistanceX * DistanceX) + (DistanceY * DistanceY);
	float RadiusSquare = Radius * Radius;
	return  DistanceSquare <= RadiusSquare;
}
