
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

class UBoxComponent;
class AEnemyBase;
class AProjectileBase;

UENUM(BlueprintType)
enum EAttribute
{
	Normal,Fire,Ice
};

UCLASS()
class HOMEDEFENCE_API ATowerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerBase();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UBoxComponent* BoxComp;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USkeletalMeshComponent* BaseMesh;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attack)
	TSubclassOf<AProjectileBase> BulletClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Attack,meta=(ExposeOnSpawn = true))
	TEnumAsByte<EAttribute> TowerAttribute;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FVector AttributColor;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attack)
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float AttackRange = 150.f;
	UPROPERTY()
	FTimerHandle AttackTimerHandle;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attack)
	float AttackRate;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attack)
	float AttackDamage;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attack)
	float CostMoney = 20;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attack)
	int Rank = 0;
	
	UPROPERTY(BlueprintReadOnly)
	AEnemyBase* TargetToAttack;
	UPROPERTY(EditAnywhere)
	bool bTraceDebug = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TraceEnemy();

	UFUNCTION()
	void Attack();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTowerClicked(AActor* TouchedActor , FKey ButtonPressed);

};
