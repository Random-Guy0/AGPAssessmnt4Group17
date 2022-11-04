// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigationNode.h"

FNavigationNode::FNavigationNode(FVector2D Position)
{
	this->Position = Position;
}

float FNavigationNode::FScore()
{
	return GScore + HScore;
}

