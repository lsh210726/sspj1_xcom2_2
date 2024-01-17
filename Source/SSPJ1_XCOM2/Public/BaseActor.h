// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadTile.h"
#include "BaseActor.generated.h"

UCLASS()
class SSPJ1_XCOM2_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	std::pair<int, int> FindCover();//¾öÆó¹° Ã£±â

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void PathFind(int row, int col);

	UFUNCTION()
	void PathTracking(float DeltaTime);

	UFUNCTION()
	AActor* FindClosestTarget();

	UFUNCTION()
	void FindPathMananger();

	TArray<ARoadTile*> openList;
	TArray<ARoadTile*> closeList;

	class APathManager* pathManager;

	FTimerHandle TimerHandle;


	TArray<FVector> paths;

	bool inMoving=false;
	bool hasPath=false;
	int32 currentWayPointIndex=0;

	float counter=0.0f;

	TArray<ARoadTile*> coverTileList;
	TArray<ARoadTile*> coverLocationTileList;

	bool move;
};
