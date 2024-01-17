// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadTile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ARoadTile::ARoadTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(80)); //set bocComp extent

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetWorldScale3D(FVector(1.6));
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Art/M_TileWalk.M_TileWalk'"));//set mesh material
	if (Material.Succeeded())
	{
		meshComp->SetMaterial(0, Material.Object);
	}


	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	boxComp->SetCollisionProfileName(TEXT("RoadTile"));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));



}

// Called when the game starts or when spawned
void ARoadTile::BeginPlay()
{
	Super::BeginPlay();
	if (boxComp != nullptr)
	{
		boxComp->OnComponentBeginOverlap.AddDynamic(this, &ARoadTile::OnTileOverlap);
		boxComp->OnComponentEndOverlap.AddDynamic(this, &ARoadTile::OnTileEndOverlap);
	}
	//startLoc = GetActorLocation();
	//SetActorLocation(FVector(1000, 1000, 1000));
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARoadTile::StartMoving, 0.2f, false);


}

// Called every frame
void ARoadTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ARoadTile::OnTileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Art/M_TileWalk.M_TileWalk'"));
	//if (Material.Succeeded())
	//{
	//	meshComp->SetMaterial(0, Material.Object);
	//}

	//UE_LOG(LogTemp, Log, TEXT("%s overlapped by %s"), *GetName(), *OtherActor->GetName());
	tileColor = FColor::Orange;
	isCanWalkTile = false;
	overlapActor = OtherActor;

	//DrawDebugBox(GetWorld(), GetActorLocation(), FVector(tileSize, tileSize, tileSize), tileColor, true, 1, 0, 10);

}

void ARoadTile::OnTileEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Log, TEXT("%s Overlap End!!"), *GetName());
	tileColor = FColor::Blue;
	isCanWalkTile = true;
	overlapActor = nullptr;
}

void ARoadTile::StartMoving()
{
	SetActorLocation(startLoc);
}

