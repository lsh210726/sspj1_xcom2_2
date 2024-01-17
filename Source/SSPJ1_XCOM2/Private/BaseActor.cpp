// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PathManager.h"
#include"EngineUtils.h"
#include <stack>
#include <utility>
#include "Kismet/KismetSystemLibrary.h"
#include "AStarSearch.h"


using namespace std;


// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);


}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseActor::PathFind, 0.2f, false);
	//PathFind();
	//FindPathMananger();

	pair<int,int> pp = findCoverLocation();

	moveLocationFinder(pp.first,pp.second);

	FTimerHandle GravityTimerHandle;
	float GravityTime=3;

	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 코드 구현
			//pathManager->RoadTileRePosition(GetActorLocation());//타일 재배치
			//std::pair<int,int> coverRowCol = FindCover();//타겟을 찾고 해당 타겟에 대한 엄폐위치를 찾는다
			//PathFind(coverRowCol.first,coverRowCol.second);//엄폐위치로 이동한다
			//UE_LOG(LogTemp, Log, TEXT("cover row : %d, cover col : %d"), coverRowCol.first, coverRowCol.second);
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
		}), GravityTime, false);

}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (move) PathTracking(DeltaTime);
}

//void ABaseActor::PathFind(int row1, int col1)//a*알고리즘을 활용한 길찾기 a* path find
//{
//	UE_LOG(LogTemp, Log, TEXT("path find start!"));
//
//	//SetActorLocation(pathManager->RoadTileArray[0][0]->GetActorLocation());
//	paths = pathManager->AStarPathFinding(row1,col1);//바닥 배열화 테스트
//	hasPath = true;
//	move = true;
//	for (FVector V : paths)
//	{
//
//	}
//}

//std::pair<int, int> ABaseActor::FindCover()
//{
//	UE_LOG(LogTemp, Log, TEXT("Find Cover"));
//	if (pathManager != nullptr)
//	{
//		auto RTA = pathManager->RoadTileArray;
//
//		for (auto i : RTA)
//		{
//			for (auto j : i)
//			{
//				ABaseActor* ba = Cast<ABaseActor>(j->overlapActor);
//				if (!j->isCanWalkTile&&!ba)//워크타일이 걸을수 없는 상태고 오버랩된 액터가 베이스액터가 아니라면 -> 엄폐물
//				{
//					UE_LOG(LogTemp, Log, TEXT("Cover tile Row = %d, Cover tile Col = %d"), j->tileRow, j->tileCol);
//					DrawDebugSphere(GetWorld(), j->GetActorLocation(), 100, 8, FColor::Yellow, true, -1, 0, 2);
//					coverTileList.Emplace(j);
//				}
//			}
//		}
//
//		for (auto i : coverTileList)//엄폐물 주변 타일 저장
//		{
//			int32 row = i->tileRow;
//			int32 col = i->tileCol;
//			if (row-1>=0&&col-1>=0&&row+1<=RTA.Num()&&col+1<=RTA[0].Num() && RTA[row-1][col]!=nullptr&&RTA[row-1][col]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row - 1][col]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row - 1][col-1] != nullptr && RTA[row - 1][col-1]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row - 1][col-1]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row - 1][col+1] != nullptr && RTA[row - 1][col+1]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row - 1][col+1]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row][col-1] != nullptr && RTA[row][col-1]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row][col-1]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row][col + 1] != nullptr && RTA[row][col + 1]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row][col + 1]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row+1][col - 1] != nullptr && RTA[row+1][col - 1]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row+1][col - 1]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row + 1][col] != nullptr && RTA[row + 1][col]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row + 1][col]);
//			}
//			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row + 1][col + 1] != nullptr && RTA[row + 1][col + 1]->isCanWalkTile)
//			{
//				coverLocationTileList.Emplace(RTA[row + 1][col + 1]);
//			}
//		}
//
//		AActor* target = FindClosestTarget();
//
//		for (auto i : coverLocationTileList)//엄폐물 주변 타일과 타깃 사이 공격 되는 타일들 제거
//		{
//			FHitResult hr;
//			if (!GetWorld()->LineTraceSingleByProfile(hr, target->GetActorLocation(), i->GetActorLocation(), TEXT("Attack")))
//			{
//				//UE_LOG(LogTemp, Log, TEXT("Line trace hit!"));
//				//coverLocationTileList.Remove(i);
//				i = nullptr;
//				//DrawDebugLine(GetWorld(), target->GetActorLocation(), i->GetActorLocation(), FColor::Emerald, true, 1, 0, 10);
//			};
//		}
//
//		for (auto i : coverLocationTileList)
//		{
//			//UE_LOG(LogTemp, Warning, TEXT("%s"),  *i->GetName());
//			if (i != nullptr) DrawDebugSphere(GetWorld(), i->GetActorLocation(), 100, 8, FColor::Purple, true, -1, 0, 2);
//		}
//
//		float closestDist=999;
//		std::pair<int, int> closestTile;
//		UE_LOG(LogTemp, Log, TEXT("Target Name : %s, Target Location : %f, %f @@@@@@@@@@@@@@@"),*target->GetName(), target->GetActorLocation().X, target->GetActorLocation().Y);
//
//		for (auto i : coverLocationTileList)
//		{
//			UE_LOG(LogTemp, Log, TEXT("row : %d, col : %d, dist : %f"),i->tileRow, i->tileCol, target->GetDistanceTo(i));
//			if (target->GetDistanceTo(i) <= closestDist)
//			{
//				closestDist = target->GetDistanceTo(i);
//				closestTile.first = i->tileRow;
//				closestTile.second = i->tileCol;
//				UE_LOG(LogTemp, Warning, TEXT("row : %d, col : %d, dist : %f"), closestTile.first, closestTile.second, closestDist);
//			}
//		}
//
//		return closestTile;//가장 적과 가까운 엄폐 위치
//	}
//	return std::make_pair(99, 99);
//}

void ABaseActor::PathTracking(float DeltaTime)
{
	if (currentWayPointIndex + 1 > paths.Num())
	{
		move = false;
	}
	else if (paths.Num() > 0 && currentWayPointIndex+1<=paths.Num())
	{
		// Get the current waypoint
		FVector Waypoint = paths[currentWayPointIndex];

		// Move the actor towards the waypoint
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Waypoint, DeltaTime, 300.0f);
		SetActorLocation(NewLocation);

		// If the actor is close to the waypoint, move to the next waypoint
		if (FVector::Distance(NewLocation, Waypoint) < 10.0f)
		{
			//currentWayPointIndex = (currentWayPointIndex + 1) % paths.Num();
			currentWayPointIndex++;
		}
	}
}

AActor* ABaseActor::FindClosestTarget()
{
	float clostDist = 9999;
	AActor* clostActor = this;
	UE_LOG(LogTemp, Log, TEXT("find closest target"));
	for (TActorIterator<AActor> a(GetWorld()); a; ++a)
	{
		if (a->GetName().Contains(TEXT("TestPlayer")))//상대방 이름
		{
			if (GetDistanceTo(*a) <= clostDist)
			{
				clostDist = GetDistanceTo(*a);
				clostActor = *a;
			}
			UE_LOG(LogTemp, Log, TEXT("%s"), *a->GetName());
			//UE_LOG(LogTemp, Log, TEXT("%s"), **clostActor->GetName());
			return *a;
		}
	}
	return nullptr;
}

void ABaseActor::FindPathMananger()
{
	//find pathmanager
	for (TActorIterator<APathManager> pm(GetWorld()); pm; ++pm)
	{
		//UE_LOG(LogTemp, Log, TEXT("PathMananger nale : %s"), *pm->GetName());
		pathManager = *pm;
	}
}

void ABaseActor::moveLocationFinder(int destRow, int destCol)
{
	//0,0 위치 찾기
	float x, y, z;
	x = GetActorLocation().X - (20 / 2 * 100 * 2);
	y = GetActorLocation().Y - (20 / 2 * 100 * 2);
	z = GetActorLocation().Z;

	FVector baseLoc = GetActorLocation();

	int mapGrid[20][20];

	for (int i = 0; i < ROW; i++)
	{
		TArray<FVector> va;
		for (int j = 0; j < COL; j++)
		{
			va.Emplace(FVector(x + (100 * 2 * i), y + (100 * 2 * j), z));

			FHitResult hr;
			
			bool bIsHit = GetWorld()->SweepSingleByProfile(
				hr,
				FVector(x + (100 * 2 * i), y + (100 * 2 * j), z),
				FVector(x + (100 * 2 * i), y + (100 * 2 * j), z),
				FQuat::Identity,
				TEXT("Pawn"),
				FCollisionShape::MakeBox(FVector(100)),
				FCollisionQueryParams(SCENE_QUERY_STAT(SweepSingle), true)
			);

			if (bIsHit && !hr.GetActor()->GetName().Contains(TEXT("BaseActor")))
			{
				DrawDebugSphere(GetWorld(), FVector(x + (100 * 2 * i), y + (100 * 2 * j), z), 100, 8, FColor::Purple, true, -1, 0, 2);
				mapGrid[i][j] = 0;//장애물
			}
			else
			{
				mapGrid[i][j] = 1;//길
			}
		}
		moveLocationArr.Emplace(va);
	}

	for (auto i : moveLocationArr)
	{
		for (auto j : i)
		{
			//UE_LOG(LogTemp, Log, TEXT("%f, %f, %f"), j.X, j.Y, j.Z);
		}
	}

	DrawDebugSphere(GetWorld(), moveLocationArr[destRow][destCol], 100, 8, FColor::Green, true, -1, 0, 2);
	UE_LOG(LogTemp, Warning, TEXT("@@@@@@@@@@@@@@@@@@@@@@@@@@@ : %f,%f,%f, %d"), moveLocationArr[destRow][destCol].X, moveLocationArr[destRow][destCol].Y, moveLocationArr[destRow][destCol].Z, mapGrid[destRow][destCol]);

	MoveToLocation(mapGrid, make_pair(ROW / 2, COL / 2), make_pair(destRow, destCol));

}

void ABaseActor::MoveToLocation(int grid1[20][20], std::pair<int, int> src, std::pair<int, int> dest)
{
	PathFind(grid1, src, dest);

	while (!pathStack.empty()) {//경로저장스택이 빌 때까지 내부 값 출력하기
		pair<int, int> p = pathStack.top();
		pathStack.pop();
		UE_LOG(LogTemp, Warning, TEXT("-> (%d,%d) "), p.first, p.second);
		paths.Emplace(moveLocationArr[p.first][p.second]);
	}
	if (pathStack.empty())move = true;
}

pair<int,int> ABaseActor::findCoverLocation()
{
	//0,0 위치 찾기
	float x, y, z;
	x = GetActorLocation().X - (20 / 2 * 100 * 2);
	y = GetActorLocation().Y - (20 / 2 * 100 * 2);
	z = GetActorLocation().Z;

	int mapGrid[20][20];

	for (int i = 0; i < ROW; i++)
	{
		TArray<FVector> va;
		for (int j = 0; j < COL; j++)
		{
			va.Emplace(FVector(x + (100 * 2 * i), y + (100 * 2 * j), z));

			FHitResult hr;

			bool bIsHit = GetWorld()->SweepSingleByProfile(
				hr,
				FVector(x + (100 * 2 * i), y + (100 * 2 * j), z),
				FVector(x + (100 * 2 * i), y + (100 * 2 * j), z),
				FQuat::Identity,
				TEXT("Pawn"),
				FCollisionShape::MakeBox(FVector(100)),
				FCollisionQueryParams(SCENE_QUERY_STAT(SweepSingle), true)
			);

			if (bIsHit && !hr.GetActor()->GetName().Contains(TEXT("BaseActor")))
			{
				mapGrid[i][j] = 0;//장애물
			}
			else
			{
				mapGrid[i][j] = 1;//길
			}
		}
		moveLocationArr.Emplace(va);
	}

	AActor* target = FindClosestTarget();
	int xx, yy;
	double distance2Target=9999;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			FHitResult hr;
			if (mapGrid[i][j]==1 && GetWorld()->LineTraceSingleByProfile(hr, target->GetActorLocation(), FVector(x + (100 * 2 * i), y + (100 * 2 * j), z), TEXT("Attack")))
			{
				double distance = (target->GetActorLocation() - FVector(x + (100 * 2 * i), y + (100 * 2 * j), z)).Size();
				if (distance < distance2Target)
				{
					distance2Target = distance;
					xx = i, yy = j;
				}
			};
		}
	}
	UE_LOG(LogTemp, Log, TEXT("find cover location : %d,%d"), xx, yy);

	return make_pair(xx, yy);
}