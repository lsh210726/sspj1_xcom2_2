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

void APathManager::RoadTileMake()//world road tile make //길찾기 위한 위치 타일 생성하기 10*10
{
	for (int i = 0; i < ROW; i++)
	{
		TArray<ARoadTile*> RA1;

		int32 tileSize = 0;
		for (int j = 0; j < COL; j++)
		{
			//나중에 박스 트레이스로 충돌 판정 후 해당 경로 장애물 있는지 판정 확인 요망
			ARoadTile* RT = GetWorld()->SpawnActor<ARoadTile>(roadTileFactory, FVector(0,0,0),FRotator(0,0,0));
			RT->SetActorLocation(FVector(iX, iY, tileSize),true);
			RA1.Add(RT);
			tileSize = RT->tileSize;
			iX += tileSize*2;
			RT->tileRow = i;
			RT->tileCol = j;
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

void APathManager::RoadTileRePosition(FVector center)//로드타일 재배치
{
	int tileSize1=0;
	if (RoadTileArray[0][0] != nullptr)
	{
		iX = center.X - (RoadTileArray[0][0]->tileSize * 2 * COL / 2); //액터의 x위치 – (타일의 반지름 * 2 * 전체 타일 열 / 2)
		iY = center.Y - (RoadTileArray[0][0]->tileSize * 2 * ROW / 2);
		tileSize1 = RoadTileArray[0][0]->tileSize;
		UE_LOG(LogTemp, Warning, TEXT("RoadTile RePosition Start Location : iX->%d, iY->%d"), iX, iY);
	}
	int ixTemp = iX;//처음 iX위치 저장 임시 변수
	for (auto RA2 : RoadTileArray)
	{
		for (auto RT2 : RA2)
		{
			RT2->SetActorLocation(FVector(iX, iY, tileSize1), true);
			iX += tileSize1 * 2;
		}
		iY += tileSize1 * 2;
		iX = ixTemp;
	}


}

TArray<FVector> APathManager::AStarPathFinding(int destRow, int destCol)
{
	int grid[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j< 10; j++)
		{
			if (RoadTileArray[i][j] != nullptr)
			{
				grid[i][j] = RoadTileArray[i][j]->isCanWalkTile;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		FString rowString;

		for (int j = 0; j < 10; j++) {
			// 각 열의 값을 rowString에 추가합니다.
			rowString += FString::Printf(TEXT("%d, "), grid[i][j]);
		}

		// 각 행의 마지막에서 로그를 출력합니다. 이럴 경우, 각 행이 별도의 로그 메시지로 출력됩니다.
		UE_LOG(LogTemp, Warning, TEXT("%s"), *rowString);
	}

	Pair src = make_pair(ROW/2, COL/2);//출발지

	Pair dest = make_pair(destRow, destCol);//도착지

	PathFind(grid, src, dest);
	stack<Pair> pathStackCopy = pathStack;

	while (!pathStack.empty()) {//경로저장스택이 빌 때까지 내부 값 출력하기
		pair<int, int> p = pathStack.top();
		pathStack.pop();
		UE_LOG(LogTemp, Warning,TEXT("-> (%d,%d) "), p.first, p.second);
		DrawDebugSphere(GetWorld(), RoadTileArray[p.first][p.second]->GetActorLocation(), 100, 8, FColor(181, 0, 0), true, -1, 0, 2);
	}

	while (!pathStackCopy.empty()) {//경로저장스택이 빌 때까지 내부 값 출력하기
		pair<int, int> p = pathStackCopy.top();
		pathStackCopy.pop();
		pathArray.Emplace(RoadTileArray[p.first][p.second]->GetActorLocation());

	}
	return pathArray;
}

