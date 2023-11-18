// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeDefence/Public/TileBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATileBase::ATileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeDefaultMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);
    if (CubeDefaultMesh.Succeeded())
    {
	    CubeMesh->SetStaticMesh(CubeDefaultMesh.Object);
    }

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneDefaultMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
	PlaneMesh->SetupAttachment(RootComponent);
    if (PlaneDefaultMesh.Succeeded())
    {
	    PlaneMesh->SetStaticMesh(PlaneDefaultMesh.Object);
    }
	PlaneMesh->SetRelativeLocation(FVector(0.f,0.f,50.1f));
	PlaneMesh->SetVisibility(false);

	
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





