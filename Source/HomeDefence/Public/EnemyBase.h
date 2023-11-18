
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

class UCapsuleComponent;
class ATileBase;
class AMapEditor;

UCLASS()
class HOMEDEFENCE_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootScene;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Movement)
	TArray<ATileBase*> EnemyPath;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Movement)
	float MoveSpeed = 100.f;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Movement)
	int CurIndex = 0;


	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float RealHealth;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int ValueMoney = 10;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float EnemyDamage = 10;
	

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Damege(AActor* DamageCauser);
	
public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateLocation(float DeltaSeconds);
};
