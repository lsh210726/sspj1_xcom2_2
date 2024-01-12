// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadTile.h"
#include "PathManager.generated.h"


UCLASS()
class SSPJ1_XCOM2_API APathManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RoadTileMake();

	TArray<TArray<ARoadTile*>> RoadTileArray;//RoadTile 2D Array

	UPROPERTY(EditAnywhere)//타일이 생성될 좌표 위치
	int iX = 0;

	UPROPERTY(EditAnywhere)//타일이 생성될 좌표 위치
	int iY = 0;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARoadTile> roadTileFactory; //roadTile Factory

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)//타일매니저가 생성할 행과 열의 크기
	int32 ROW = 10;
	UPROPERTY(EditAnywhere)
	int32 COL = 10;

	UFUNCTION()
	TArray<FVector> AStarPathFinding();

	TArray<FVector> pathArray;
};
