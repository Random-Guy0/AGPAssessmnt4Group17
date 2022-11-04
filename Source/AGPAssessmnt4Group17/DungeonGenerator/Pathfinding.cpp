// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding.h"

FPathfinding::FPathfinding(TArray<FVector2D> Vertices, int32 GridWidth, int32 GridDepth)
{
	this->GridWidth = GridWidth;
	this->GridDepth = GridDepth;

	AllNodes.SetNum(Vertices.Num());

	for(int32 I = 0; I < GridWidth; I++)
	{
		for(int32 J = 0; J < GridDepth; J++)
		{
			if(!Vertices[J * GridWidth + I].Equals(FVector2D(-1, -1)))
			{
				AllNodes[J * GridWidth + I] = new FNavigationNode(Vertices[J * GridWidth + I]);
			}
		}
	}

	for (int32 I = 0; I < GridWidth; I++)
	{
		for (int32 J = 0; J < GridDepth; J++)
		{
			if(AllNodes[J * GridWidth + I])
			{
				if (I - 1 >= 0 && AllNodes[J * GridWidth + (I - 1)])
				{
					AllNodes[J * GridWidth + I]->ConnectedNodes.Add(AllNodes[J * GridWidth + (I - 1)]);
				}

				if (I + 1 < GridWidth && AllNodes[J * GridWidth + (I + 1)])
				{
					AllNodes[J * GridWidth + I]->ConnectedNodes.Add(AllNodes[J * GridWidth + (I + 1)]);
				}

				if (J - 1 >= 0 && AllNodes[(J - 1) * GridWidth + I])
				{
					AllNodes[J * GridWidth + I]->ConnectedNodes.Add(AllNodes[(J - 1) * GridWidth + I]);
				}

				if (J + 1 < GridDepth && AllNodes[(J + 1) * GridWidth + I])
				{
					AllNodes[J * GridWidth + I]->ConnectedNodes.Add(AllNodes[(J + 1) * GridWidth + I]);
				}
			}
		}
	}
}

TArray<FVector2D> FPathfinding::GeneratePath(FVector2D Start, FVector2D End)
{
	FNavigationNode* StartNode = AllNodes[Start.Y * GridWidth + Start.X];

	if(!StartNode)
	{
		StartNode = new FNavigationNode(Start);
		AllNodes[Start.Y * GridWidth + Start.X] = StartNode;

		if (Start.X + 1 < GridWidth && AllNodes[Start.Y * GridWidth + (Start.X + 1)])
		{
			StartNode->ConnectedNodes.Add(AllNodes[Start.Y * GridWidth + (Start.X + 1)]);
			AllNodes[Start.Y * GridWidth + (Start.X + 1)]->ConnectedNodes.Add(StartNode);
		}

		if (Start.X - 1 >= 0 && AllNodes[Start.Y * GridWidth + (Start.X - 1)])
		{
			StartNode->ConnectedNodes.Add(AllNodes[Start.Y * GridWidth + (Start.X - 1)]);
			AllNodes[Start.Y * GridWidth + (Start.X - 1)]->ConnectedNodes.Add(StartNode);
		}

		if (Start.Y + 1 < GridDepth && AllNodes[(Start.Y + 1) * GridWidth + Start.X])
		{
			StartNode->ConnectedNodes.Add(AllNodes[(Start.Y + 1) * GridWidth + Start.X]);
			AllNodes[(Start.Y + 1) * GridWidth + Start.X]->ConnectedNodes.Add(StartNode);
		}

		if (Start.Y - 1 >= 0 && AllNodes[(Start.Y - 1) * GridWidth + Start.X])
		{
			StartNode->ConnectedNodes.Add(AllNodes[(Start.Y - 1) * GridWidth + Start.X]);
			AllNodes[(Start.Y - 1) * GridWidth + Start.X]->ConnectedNodes.Add(StartNode);
		}
	}

	FNavigationNode* EndNode = AllNodes[End.Y * GridWidth + End.X];

	if(!EndNode)
	{
		EndNode = new FNavigationNode(End);
		AllNodes[End.Y * GridWidth + End.X] = EndNode;

		if (End.X + 1 < GridWidth && AllNodes[End.Y * GridWidth + (End.X + 1)])
		{
			EndNode->ConnectedNodes.Add(AllNodes[End.Y * GridWidth + (End.X + 1)]);
			AllNodes[End.Y * GridWidth + (End.X + 1)]->ConnectedNodes.Add(EndNode);
		}

		if (End.X - 1 >= 0 && AllNodes[End.Y * GridWidth + (End.X - 1)])
		{
			EndNode->ConnectedNodes.Add(AllNodes[End.Y * GridWidth + (End.X - 1)]);
			AllNodes[End.Y * GridWidth + (End.X - 1)]->ConnectedNodes.Add(EndNode);
		}

		if (End.Y + 1 < GridDepth && AllNodes[(End.Y + 1) * GridWidth + End.X])
		{
			EndNode->ConnectedNodes.Add(AllNodes[(End.Y + 1) * GridWidth + End.X]);
			AllNodes[(End.Y + 1) * GridWidth + End.X]->ConnectedNodes.Add(EndNode);
		}

		if (End.Y - 1 >= 0 && AllNodes[(End.Y - 1) * GridWidth + End.X])
		{
			EndNode->ConnectedNodes.Add(AllNodes[(End.Y - 1) * GridWidth + End.X]);
			AllNodes[(End.Y - 1) * GridWidth + End.X]->ConnectedNodes.Add(EndNode);
		}
	}
	
	TArray<FNavigationNode*> NodePath = GeneratePath(StartNode, EndNode);
	TArray<FVector2D> Path;

	for (FNavigationNode* Node : NodePath)
	{
		Path.Add(Node->Position);
	}
	
	return Path;
}

TArray<FNavigationNode*> FPathfinding::GeneratePath(FNavigationNode* StartNode, FNavigationNode* EndNode)
{
	TArray<FNavigationNode*> OpenSet;
	OpenSet.Add(StartNode);

	for (FNavigationNode* Node : AllNodes)
	{
		if(Node)
		{
			Node->GScore = TNumericLimits<float>::Max();
		}
	}

	StartNode->GScore = 0.0f;
	StartNode->HScore = FVector2D::Distance(StartNode->Position, EndNode->Position);

	while (OpenSet.Num() > 0)
	{
		FNavigationNode* CurrentNode = OpenSet[0];

		for (FNavigationNode* Node : OpenSet)
		{
			if (Node->FScore() < CurrentNode->FScore())
			{
				CurrentNode = Node;
			}
		}

		OpenSet.Remove(CurrentNode);

		if (CurrentNode == EndNode)
		{
			return ReconstructPath(StartNode, EndNode);
		}

		for (FNavigationNode* ConnectedNode : CurrentNode->ConnectedNodes)
		{
			float TentativeGScore = CurrentNode->GScore + FVector2D::Distance(ConnectedNode->Position, EndNode->Position);

			if (TentativeGScore < ConnectedNode->GScore)
			{
				ConnectedNode->CameFrom = CurrentNode;
				ConnectedNode->GScore = TentativeGScore;
				ConnectedNode->HScore = FVector2D::Distance(ConnectedNode->Position, EndNode->Position);

				if (!OpenSet.Contains(ConnectedNode))
				{
					OpenSet.Add(ConnectedNode);
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Pathfinding failed :("));
	return TArray<FNavigationNode*>();
}

TArray<FNavigationNode*> FPathfinding::ReconstructPath(FNavigationNode* StartNode, FNavigationNode* EndNode)
{
	TArray<FNavigationNode*> Path;

	FNavigationNode* CurrentNode = EndNode;
	while (CurrentNode != StartNode)
	{
		Path.Add(CurrentNode);
		CurrentNode = CurrentNode->CameFrom;
	}
	return Path;
}
