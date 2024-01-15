// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadTile.generated.h"

UCLASS()
class SSPJ1_XCOM2_API ARoadTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	int tileSize = 100;

	UFUNCTION()
	void OnTileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTileEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool isCanWalkTile = true;

	FTimerHandle TimerHandle;

	UFUNCTION()
	void StartMoving();

	FVector startLoc;

	FColor tileColor = FColor::Blue;

	AActor* overlapActor; // 오버랩된 액터 포인터

	int32 tileRow;
	int32 tileCol;
};
