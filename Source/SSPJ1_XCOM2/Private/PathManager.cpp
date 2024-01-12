// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"
#include "RoadTile.h"
#include <stack>
#include <utility>
#include "AStarSearch.h"
#include "DrawDebugHelpers.h"

using namespace std;


// Sets default values
APathManager::APathManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathManager::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APathManager::RoadTileMake, 0.2f, false);
	RoadTileMake();

}

// Called every frame
void APathManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APathManager::RoadTileMake()//world road tile make //��ã�� ���� ��ġ Ÿ�� �����ϱ� 10*10
{
	for (int i = 0; i < ROW; i++)
	{
		TArray<ARoadTile*> RA1;

		int32 tileSize = 0;
		for (int j = 0; j < COL; j++)
		{
			//���߿� �ڽ� Ʈ���̽��� �浹 ���� �� �ش� ��� ��ֹ� �ִ��� ���� Ȯ�� ���
			ARoadTile* RT = GetWorld()->SpawnActor<ARoadTile>(roadTileFactory, FVector(0,0,0),FRotator(0,0,0));
			RT->SetActorLocation(FVector(iX, iY, tileSize),true);
			RA1.Add(RT);
			tileSize = RT->tileSize;
			iX += tileSize*2;
		}
		RoadTileArray.Add(RA1);
		iY += tileSize*2;
		iX = 0;
	}

	//for (const TArray<ARoadTile*>& RA1 : RoadTileArray)
	//{
	//	for (ARoadTile* RT1 : RA1)
	//	{
	//		if (RT1) UE_LOG(LogTemp, Log, TEXT("tileName : %s"), *RT1->GetName());
	//	}
	//}

	//for (int32 i = 0; i < ROW; i++)
	//{
	//	for (int32 j = 0; j < COL; j++)
	//	{
	//		if (RoadTileArray[i][j] != nullptr)UE_LOG(LogTemp, Log, TEXT("tileName2 = %s"), *RoadTileArray[i][j]->GetName());
	//	}
	//}
}

TArray<FVector> APathManager::AStarPathFinding()
{
	int grid[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j< 10; j++)
		{
			if (RoadTileArray[i][j] != nullptr)
			{
				grid[i][j] = RoadTileArray[i][j]->isCanWalkTile;
				UE_LOG(LogTemp, Log, TEXT("%d"), grid[i][j]);
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		FString rowString;

		for (int j = 0; j < 10; j++) {
			// �� ���� ���� rowString�� �߰��մϴ�.
			rowString += FString::Printf(TEXT("%d, "), grid[i][j]);
		}

		// �� ���� ���������� �α׸� ����մϴ�. �̷� ���, �� ���� ������ �α� �޽����� ��µ˴ϴ�.
		UE_LOG(LogTemp, Warning, TEXT("%s"), *rowString);
	}

	Pair src = make_pair(0, 0);

	Pair dest = make_pair(9, 9);

	PathFind(grid, src, dest);
	stack<Pair> pathStackCopy = pathStack;

	while (!pathStack.empty()) {//������彺���� �� ������ ���� �� ����ϱ�
		pair<int, int> p = pathStack.top();
		pathStack.pop();
		UE_LOG(LogTemp, Warning,TEXT("-> (%d,%d) "), p.first, p.second);
		DrawDebugSphere(GetWorld(), RoadTileArray[p.first][p.second]->GetActorLocation(), 100, 8, FColor(181, 0, 0), true, -1, 0, 2);
	}

	while (!pathStackCopy.empty()) {//������彺���� �� ������ ���� �� ����ϱ�
		pair<int, int> p = pathStackCopy.top();
		pathStackCopy.pop();
		pathArray.Emplace(RoadTileArray[p.first][p.second]->GetActorLocation());

	}
	return pathArray;
}

