
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemys.generated.h"

class AEnemyBase;

USTRUCT(BlueprintType)
struct FEnemyWaves
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<AEnemyBase> EnemyClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float EnemyAmount;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float EnemyMaxHealth;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float EnemyMoveSpeed;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float SpawnRateInteral;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float EnemyValueMoney;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float EnemyDamage;
};

UCLASS()
class HOMEDEFENCE_API ASpawnEnemys : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnEnemys();

	UPROPERTY()
	FTimerHandle SpawnTimer;
	
	UPROPERTY()
	int EnemyAmount = 0;
	UPROPERTY()
	int TotalAmount = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<FEnemyWaves> EnemyWaves;
	UPROPERTY(EditDefaultsOnly)
	float InitialTime = 5.f;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int WaveIndex = -1;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ControlSpawning();
	
	UFUNCTION()
	void SpawningEnemy();

};
