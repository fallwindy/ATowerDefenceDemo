
#include "SpawnEnemys.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

ASpawnEnemys::ASpawnEnemys()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASpawnEnemys::BeginPlay()
{
	Super::BeginPlay();
	for (auto EnemyWave : EnemyWaves)
	{
		TotalAmount += EnemyWave.EnemyAmount;
	}
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this,&ASpawnEnemys::ControlSpawning,InitialTime,false);
	
}


void ASpawnEnemys::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnEnemys::ControlSpawning()
{
	EnemyAmount = 0;
	WaveIndex += 1;
	if (EnemyWaves.IsValidIndex(WaveIndex))
	{
		float SpawnInterval = EnemyWaves[WaveIndex].SpawnRateInteral;
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this,&ASpawnEnemys::SpawningEnemy,SpawnInterval,true,5.f);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnEnemys::SpawningEnemy()
{
	if(!EnemyWaves.IsValidIndex(WaveIndex))return;
	
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	auto const CurClass = EnemyWaves[WaveIndex].EnemyClass;
	auto const CurSpeed = EnemyWaves[WaveIndex].EnemyMoveSpeed;
	auto const CurMaxHealth = EnemyWaves[WaveIndex].EnemyMaxHealth;
	auto const CurValueMoney = EnemyWaves[WaveIndex].EnemyValueMoney;
	auto const CurDamage = EnemyWaves[WaveIndex].EnemyDamage;
	if(auto SpawnedEnemy = GetWorld()->SpawnActor<AEnemyBase>(CurClass,GetActorLocation(),FRotator::ZeroRotator,Params))
	{
		SpawnedEnemy->MoveSpeed = CurSpeed;
		SpawnedEnemy->MaxHealth = CurMaxHealth;
		SpawnedEnemy->RealHealth = CurMaxHealth;
		SpawnedEnemy->ValueMoney = CurValueMoney;
		SpawnedEnemy->EnemyDamage = CurDamage;
		EnemyAmount++;
	}

	if (EnemyAmount==EnemyWaves[WaveIndex].EnemyAmount)
	{
		EnemyAmount = 0;
		ControlSpawning();
	}
	
}

