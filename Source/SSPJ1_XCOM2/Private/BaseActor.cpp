// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PathManager.h"
#include"EngineUtils.h"
#include <stack>
#include <utility>



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
	FindPathMananger();

	FTimerHandle GravityTimerHandle;
	float GravityTime=3;

	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 코드 구현
			pathManager->RoadTileRePosition(GetActorLocation());//타일 재배치
			std::pair<int,int> coverRowCol = FindCover();//타겟을 찾고 해당 타겟에 대한 엄폐위치를 찾는다
			PathFind(coverRowCol.first,coverRowCol.second);//엄폐위치로 이동한다
			//UE_LOG(LogTemp, Log, TEXT("cover row : %d, cover col : %d"), coverRowCol.first, coverRowCol.second);
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
		}), GravityTime, false);

}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (paths.Num() > 0 && currentWayPointIndex+1<=paths.Num())
	//{
	//	// Get the current waypoint
	//	FVector Waypoint = paths[currentWayPointIndex];

	//	// Move the actor towards the waypoint
	//	FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Waypoint, DeltaTime, 300.0f);
	//	SetActorLocation(NewLocation);

	//	// If the actor is close to the waypoint, move to the next waypoint
	//	if (FVector::Distance(NewLocation, Waypoint) < 10.0f)
	//	{
	//		//currentWayPointIndex = (currentWayPointIndex + 1) % paths.Num();
	//		currentWayPointIndex++;
	//	}
	//}

	if (move) PathTracking(DeltaTime);
}

void ABaseActor::PathFind(int row, int col)//a*알고리즘을 활용한 길찾기 a* path find
{
	UE_LOG(LogTemp, Log, TEXT("path find start!"));

	//SetActorLocation(pathManager->RoadTileArray[0][0]->GetActorLocation());
	paths = pathManager->AStarPathFinding(row,col);//바닥 배열화 테스트
	hasPath = true;
	move = true;
	for (FVector V : paths)
	{

	}
}

std::pair<int, int> ABaseActor::FindCover()
{
	UE_LOG(LogTemp, Log, TEXT("Find Cover"));
	if (pathManager != nullptr)
	{
		auto RTA = pathManager->RoadTileArray;

		for (auto i : RTA)
		{
			for (auto j : i)
			{
				ABaseActor* ba = Cast<ABaseActor>(j->overlapActor);
				if (!j->isCanWalkTile&&!ba)//워크타일이 걸을수 없는 상태고 오버랩된 액터가 베이스액터가 아니라면 -> 엄폐물
				{
					UE_LOG(LogTemp, Log, TEXT("Cover tile Row = %d, Cover tile Col = %d"), j->tileRow, j->tileCol);
					DrawDebugSphere(GetWorld(), j->GetActorLocation(), 100, 8, FColor::Yellow, true, -1, 0, 2);
					coverTileList.Emplace(j);
				}
			}
		}

		for (auto i : coverTileList)//엄폐물 주변 타일 저장
		{
			int32 row = i->tileRow;
			int32 col = i->tileCol;
			if (row-1>=0&&col-1>=0&&row+1<=RTA.Num()&&col+1<=RTA[0].Num() && RTA[row-1][col]!=nullptr&&RTA[row-1][col]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row - 1][col]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row - 1][col-1] != nullptr && RTA[row - 1][col-1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row - 1][col-1]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row - 1][col+1] != nullptr && RTA[row - 1][col+1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row - 1][col+1]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row][col-1] != nullptr && RTA[row][col-1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row][col-1]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row][col + 1] != nullptr && RTA[row][col + 1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row][col + 1]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row+1][col - 1] != nullptr && RTA[row+1][col - 1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row+1][col - 1]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row + 1][col] != nullptr && RTA[row + 1][col]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row + 1][col]);
			}
			if (row - 1 >= 0 && col - 1 >= 0 && row + 1 <= RTA.Num() && col + 1 <= RTA[0].Num() && RTA[row + 1][col + 1] != nullptr && RTA[row + 1][col + 1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row + 1][col + 1]);
			}
		}

		AActor* target = FindClosestTarget();

		for (auto i : coverLocationTileList)//엄폐물 주변 타일과 타깃 사이 공격 되는 타일들 제거
		{
			FHitResult hr;
			if (!GetWorld()->LineTraceSingleByProfile(hr, target->GetActorLocation(), i->GetActorLocation(), TEXT("Attack")))
			{
				//UE_LOG(LogTemp, Log, TEXT("Line trace hit!"));
				//coverLocationTileList.Remove(i);
				i = nullptr;
				//DrawDebugLine(GetWorld(), target->GetActorLocation(), i->GetActorLocation(), FColor::Emerald, true, 1, 0, 10);
			};
		}

		for (auto i : coverLocationTileList)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s"),  *i->GetName());
			if (i != nullptr) DrawDebugSphere(GetWorld(), i->GetActorLocation(), 100, 8, FColor::Purple, true, -1, 0, 2);
		}

		float closestDist=999;
		std::pair<int, int> closestTile;
		UE_LOG(LogTemp, Log, TEXT("Target Name : %s, Target Location : %f, %f @@@@@@@@@@@@@@@"),*target->GetName(), target->GetActorLocation().X, target->GetActorLocation().Y);

		for (auto i : coverLocationTileList)
		{
			UE_LOG(LogTemp, Log, TEXT("row : %d, col : %d, dist : %f"),i->tileRow, i->tileCol, target->GetDistanceTo(i));
			if (target->GetDistanceTo(i) <= closestDist)
			{
				closestDist = target->GetDistanceTo(i);
				closestTile.first = i->tileRow;
				closestTile.second = i->tileCol;
				UE_LOG(LogTemp, Warning, TEXT("row : %d, col : %d, dist : %f"), closestTile.first, closestTile.second, closestDist);
			}
		}

		return closestTile;//가장 적과 가까운 엄폐 위치
	}
	return std::make_pair(99, 99);
}

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
	float clostDist = 999;
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