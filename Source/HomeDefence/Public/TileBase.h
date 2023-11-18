// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

UENUM(BlueprintType)
enum ETileType
{
	Grass,Road,River
};

UCLASS()
class HOMEDEFENCE_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileBase();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* CubeMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* PlaneMesh;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<ETileType> TileType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHasTower = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int X_Coorinate;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int Y_Coordinate;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int Cost = INT_MAX;//表示默认不可达

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
