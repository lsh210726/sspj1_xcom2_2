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
#include "EnemyFSM.h"



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

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();

	//pair<int,int> pp = findCoverLocation();

	//moveLocationFinder(pp.first,pp.second);

	//FindCoverNMove();
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (move) PathTracking(DeltaTime);
}

void ABaseActor::PathTracking(float DeltaTime)
{
	if (currentWayPointIndex + 1 > paths.Num())
	{
		move = false;
	}
	else if (paths.Num() > 0 && currentWayPointIndex + 1 <= paths.Num())
	{
		// Get the current waypoint
		FVector Waypoint = paths[currentWayPointIndex];

		// Move the actor towards the waypoint
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Waypoint, DeltaTime, 300.0f);
		//SetActorLocation(NewLocation);


		// 액터의 현재 위치를 가져옵니다.
		FVector CurrentLocation = GetActorLocation();

		// 타겟 방향을 구하기 위해, 타겟 위치에서 현재 위치를 뺍니다.
		FVector DirectionToTarget = (NewLocation - CurrentLocation).GetSafeNormal();

		// DirectionToTarget 벡터를 바탕으로 새로운 회전값을 구합니다.
		FRotator TargetRotation = DirectionToTarget.ToOrientationRotator();

		float RotationSpeed = 15.0f;
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

		// 액터의 회전을 새로운 회전값으로 설정합니다.
		SetActorRotation(NewRotation);

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
		if (a->GetName().Contains(TEXT("BP_Player")))//상대방 이름
		{
			if (GetDistanceTo(*a) <= clostDist)
			{
				clostDist = GetDistanceTo(*a);
				clostActor = *a;
			}
			return *a;
		}
	}
	return nullptr;
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
				//DrawDebugSphere(GetWorld(), FVector(x + (100 * 2 * i), y + (100 * 2 * j), z), 100, 8, FColor::Purple, true, 1.0f, 0, 2);
				mapGrid[i][j] = 0;//장애물
			}
			else
			{
				mapGrid[i][j] = 1;//길
			}
		}
		//moveLocationArr.Emplace(va);
		//UE_LOG(LogTemp, Log, TEXT("Im here %f %f %f, %f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z, moveLocationArr[ROW / 2][COL / 2].X, moveLocationArr[ROW / 2][COL / 2].Y, moveLocationArr[ROW / 2][COL / 2].Z);
	}

	//DrawDebugSphere(GetWorld(), moveLocationArr[destRow][destCol], 120, 8, FColor::Green, true, 1.0f, 0, 2);

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

		//for (int k = 0; k < ROW; k++) {
		//	// 각 행을 순회할 때마다 새로운 FString을 시작합니다.
		//	FString rowString;

		//	for (int l = 0; l < COL; l++) {
		//		// 각 열의 값을 rowString에 추가합니다.
		//		rowString += FString::Printf(TEXT("%d, "), mapGrid[k][l]);
		//	}

		//	// 각 행의 마지막에서 로그를 출력합니다. 이럴 경우, 각 행이 별도의 로그 메시지로 출력됩니다.
		//	UE_LOG(LogTemp, Warning, TEXT("%s"), *rowString);
		//}
	}

	target = FindClosestTarget();
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
				//UE_LOG(LogTemp, Log, TEXT("x : %f, y : %f, z : %f, dist : %f"), x + (100 * 2 * i), y + (100 * 2 * j), z, distance);
				//DrawDebugSphere(GetWorld(), FVector(x + (100 * 2 * i), y + (100 * 2 * j), z), 100, 8, FColor::Yellow, true, 1.0f, 0, 2);

			};
		}
	}
	UE_LOG(LogTemp, Log, TEXT("find cover location : %d,%d"), xx, yy);
	if (xx<-1 || xx>ROW || yy<-1 || yy>COL)//만약 숨을곳이 없다면
	{
		xx = ROW / 2, yy = COL / 2;
		UE_LOG(LogTemp, Warning, TEXT("No Place To Cover!!!"));
	}
	return make_pair(xx, yy);
}

void ABaseActor::FindCoverNMove()
{
	pair<int, int> pp = findCoverLocation();
	UE_LOG(LogTemp, Log, TEXT("dest : %d,%d"), pp.first, pp.second);
	moveLocationFinder(pp.first, pp.second);
}