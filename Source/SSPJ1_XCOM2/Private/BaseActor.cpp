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
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseActor::PathFind, 0.2f, false);
	//PathFind();

	FTimerHandle GravityTimerHandle;
	float GravityTime=3;

	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// �ڵ� ����
			UE_LOG(LogTemp, Warning, TEXT("RoadTileRePositionStart!!!!!!!!!!"));
			pathManager->RoadTileRePosition(GetActorLocation());
			FindCover();
			// TimerHandle �ʱ�ȭ
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
}

void ABaseActor::PathFind()//a*�˰����� Ȱ���� ��ã�� a* path find
{
	UE_LOG(LogTemp, Log, TEXT("path find start!"));
	//find pathmanager
	for (TActorIterator<APathManager> pm(GetWorld()); pm; ++pm)
	{
		//UE_LOG(LogTemp, Log, TEXT("PathMananger nale : %s"), *pm->GetName());
		pathManager = *pm;
	}

	//SetActorLocation(pathManager->RoadTileArray[0][0]->GetActorLocation());
	paths = pathManager->AStarPathFinding();//�ٴ� �迭ȭ �׽�Ʈ
	hasPath = true;
	for (FVector V : paths)
	{

	}
}

void ABaseActor::FindCover()
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
				if (!j->isCanWalkTile&&!ba)//��ũŸ���� ������ ���� ���°� �������� ���Ͱ� ���̽����Ͱ� �ƴ϶�� -> ����
				{
					UE_LOG(LogTemp, Log, TEXT("Cover tile Row = %d, Cover tile Col = %d"), j->tileRow, j->tileCol);
					DrawDebugSphere(GetWorld(), j->GetActorLocation(), 100, 8, FColor::Yellow, true, -1, 0, 2);
					coverTileList.Emplace(j);
				}
			}
		}

		for (auto i : coverTileList)//���� �ֺ� Ÿ�� ����
		{
			int32 row = i->tileRow;
			int32 col = i->tileCol;
			if (RTA[row-1][col]!=nullptr&&RTA[row-1][col]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row - 1][col]);
			}
			if (RTA[row - 1][col-1] != nullptr && RTA[row - 1][col-1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row - 1][col-1]);
			}
			if (RTA[row - 1][col+1] != nullptr && RTA[row - 1][col+1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row - 1][col+1]);
			}
			if (RTA[row][col-1] != nullptr && RTA[row][col-1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row][col-1]);
			}
			if (RTA[row][col + 1] != nullptr && RTA[row][col + 1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row][col + 1]);
			}
			if (RTA[row+1][col - 1] != nullptr && RTA[row+1][col - 1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row+1][col - 1]);
			}
			if (RTA[row + 1][col] != nullptr && RTA[row + 1][col]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row + 1][col]);
			}
			if (RTA[row + 1][col + 1] != nullptr && RTA[row + 1][col + 1]->isCanWalkTile)
			{
				coverLocationTileList.Emplace(RTA[row + 1][col + 1]);
			}
		}

		for (auto i : coverLocationTileList)//���� �ֺ� Ÿ�ϰ� Ÿ�� ���� ���� �Ǵ� Ÿ�ϵ� ����
		{
			FHitResult hr;
			if (!GetWorld()->LineTraceSingleByProfile(hr, FVector(0), i->GetActorLocation(), TEXT("Attack")))
			{
				//UE_LOG(LogTemp, Log, TEXT("Line trace hit!"));
				coverLocationTileList.Remove(i);
			};
		}

		for (auto i : coverLocationTileList)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s"),  *i->GetName());
			DrawDebugSphere(GetWorld(), i->GetActorLocation(), 100, 8, FColor::Purple, true, -1, 0, 2);

		}
	}
}

