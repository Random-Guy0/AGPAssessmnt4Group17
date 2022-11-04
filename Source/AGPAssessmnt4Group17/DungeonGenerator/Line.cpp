// Fill out your copyright notice in the Description page of Project Settings.


#include "Line.h"

FLine::FLine(FVector2D Point1, FVector2D Point2)
{
	A = Point1.Y - Point2.Y;
	B = Point1.X - Point2.X;
	C = Point1.X * Point2.Y - Point2.X * Point1.Y;
}

FLine FLine::GetPerpendicularLine(FVector2D Point)
{
	return FLine(A, B, Point);
}

FVector2D FLine::GetIntersectionPoint(FLine OtherLine)
{
	float X = (B * OtherLine.C - OtherLine.B * C) / (A * OtherLine.B - OtherLine.A * B);
	float Y = (C * OtherLine.A - A * OtherLine.C) / (A * OtherLine.B - OtherLine.A * B);
	return FVector2D(X, Y);
}

FLine::FLine(float PerpendicularA, float PerpendicularB, FVector2D Point)
{
	A = PerpendicularB;
	B = -PerpendicularA;

	C = A * Point.X + B * Point.Y;
}
