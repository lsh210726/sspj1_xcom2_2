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
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (paths.Num() > 0 && currentWayPointIndex+1<=paths.Num())
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

void ABaseActor::PathFind()//a*알고리즘을 활용한 길찾기 a* path find
{
	UE_LOG(LogTemp, Log, TEXT("path find start!"));
	//find pathmanager
	for (TActorIterator<APathManager> pm(GetWorld()); pm; ++pm)
	{
		//UE_LOG(LogTemp, Log, TEXT("PathMananger nale : %s"), *pm->GetName());
		pathManager = *pm;
	}

	SetActorLocation(pathManager->RoadTileArray[0][0]->GetActorLocation());
	paths = pathManager->AStarPathFinding();//바닥 배열화 테스트
	hasPath = true;
	for (FVector V : paths)
	{

	}
}


