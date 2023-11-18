

#include "EnemyBase.h"
#include "MapEditor.h"
#include "MyGameStateBase.h"
#include "TileBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AEnemyBase::AEnemyBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	Mesh->SetGenerateOverlapEvents(true);

}


void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	RealHealth = MaxHealth;
	if(auto Mapeditor = Cast<AMapEditor>(UGameplayStatics::GetActorOfClass(GetWorld(),AMapEditor::StaticClass())))
	{
		UE_LOG(LogTemp,Warning,TEXT("get path"))
		EnemyPath = Mapeditor->Path;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("do not get mapeditor path "))
	}
}


void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLocation(DeltaTime);

}


void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::UpdateLocation(float DeltaSeconds)
{
	if(CurIndex>=EnemyPath.Num())return;
	FVector From = GetActorLocation();
	FVector To = EnemyPath[CurIndex]->GetActorLocation() + FVector(0.f,0.f,50.1f);
	if (UKismetMathLibrary::Vector_Distance(From,To)>1.f)
	{
		auto Offset = UKismetMathLibrary::Normal(To-From) * MoveSpeed * DeltaSeconds;
		AddActorWorldOffset(Offset);
		SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(),UKismetMathLibrary::MakeRotFromX(Offset),DeltaSeconds,5.f));
	}
	else
	{
		CurIndex++;
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	RealHealth -= DamageAmount;
	BP_Damege(DamageCauser);
	if (RealHealth <= 0)
	{
		//UE_LOG(LogTemp,Warning,TEXT("EnemyBase:Die!"))
		if(auto Gamestate = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
		{
			Gamestate->ChangeEnemyAmount(-1);
			Gamestate->ChangeMoney(ValueMoney);
		}
		Destroy();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

