
#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class HOMEDEFENCE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectileBase();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USphereComponent* OutCollision;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float DamageVal = 10.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ExposeOnSpawn = true))
	TEnumAsByte<EAttribute> ProjectileAttribute;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FVector AttributeColor;
	UPROPERTY()
	TSubclassOf<UDamageType> DamagTypeClass;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()	
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
