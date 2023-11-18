// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapEditor.generated.h"

class ATileBase;

UCLASS()
class HOMEDEFENCE_API AMapEditor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMapEditor();
/*
 *10*12
 *
 *[900,0]
 * ^
 * |
 *...
 * [0,0] ...-> [0,1100]  
 */

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileBase> TileClass;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<ATileBase*> Board;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int Max_X = 10;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int Max_Y = 12;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Path)
	ATileBase* Start;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Path)
	ATileBase* End;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Path)
	TArray<ATileBase*> Path;


	virtual void OnConstruction(const FTransform& Transform) override;


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnTiles();

	UFUNCTION(BlueprintCallable)
	void FindPath();

};


