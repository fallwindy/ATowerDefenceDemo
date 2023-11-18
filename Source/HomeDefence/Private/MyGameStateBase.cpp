
#include "MyGameStateBase.h"

void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	RealHealth = MyMaxHealth;

}

void AMyGameStateBase::ChangeMoney(float Val)
{
	Money += Val;
}

void AMyGameStateBase::ChangeHealth(float Val)
{
	RealHealth += Val;
	if (RealHealth <= 0)
	{
		RealHealth = 0;
		ZeroHealth();
	}
}

void AMyGameStateBase::ChangeEnemyAmount(int val)
{
	TotalEnemys += val;
	if (TotalEnemys==0)
	{
		WinGame();
	}
}

void AMyGameStateBase::SetEnemyTotalAmount(int val)
{
	TotalEnemys = val;
}


