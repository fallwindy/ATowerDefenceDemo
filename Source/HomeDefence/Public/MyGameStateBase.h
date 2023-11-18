
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"


UCLASS()
class HOMEDEFENCE_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Money = 10;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float MyMaxHealth = 100;
	UPROPERTY(BlueprintReadWrite)
	float RealHealth;

	UPROPERTY()
	int TotalEnemys = 26;


	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void ChangeMoney(float Val);

	UFUNCTION(BlueprintCallable)
	void ChangeHealth(float Val);

	UFUNCTION(BlueprintCallable)
	void ChangeEnemyAmount(int val);

	UFUNCTION()
	void SetEnemyTotalAmount(int val);

	UFUNCTION(BlueprintImplementableEvent)
	void ZeroHealth();
	UFUNCTION(BlueprintImplementableEvent)
	void WinGame();
};
