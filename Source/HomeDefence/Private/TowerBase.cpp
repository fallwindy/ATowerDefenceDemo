
#include "TowerBase.h"
#include "EnemyBase.h"
#include "ProjectileBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ATowerBase::ATowerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Boxcomp"));
	RootComponent = BoxComp;
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(BaseMesh);

	OnClicked.AddDynamic(this,&ATowerBase::OnTowerClicked);
}


void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,this,&ATowerBase::Attack,AttackRate,true,0);
	switch (TowerAttribute)
	{
	case Normal:
		{
			AttributColor = FVector(1,1,1);
			break;
		}
	case Fire:
		{
			AttributColor = FVector(1,0,0);
			break;
		}
	case Ice:
		{
			AttributColor = FVector(0,0,1);
			break;
		}
	default:
		break;
	}
	
	BaseMesh->SetVectorParameterValueOnMaterials(FName("Color"),AttributColor);
	GunMesh->SetVectorParameterValueOnMaterials(FName("Color"),AttributColor);
}


void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceEnemy();
}

void ATowerBase::TraceEnemy()
{
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0.f,0.f,100.f);
	TArray<FHitResult> HitResults;
	
	if(UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetWorld(),
		Start,
		End,
		FVector(AttackRange,AttackRange,100.f),
		FRotator::ZeroRotator,
		{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)},
		false,
		{this},
		bTraceDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		HitResults,
		true
	))
	{
		TargetToAttack = Cast<AEnemyBase>(HitResults[0].Actor);
		/*float MinDist = 500.f;
		for (auto HitResult : HitResults)
		{
			if(UKismetMathLibrary::Vector_Distance(GetActorLocation(),HitResult.Actor->GetActorLocation())<=MinDist)
			{
				TargetToAttack = Cast<AEnemyBase>(HitResult.Actor);
			}
		}*/
	}
	else
	{
		TargetToAttack = nullptr;
	}
}

void ATowerBase::Attack()
{
	if(!TargetToAttack)
	{
		return;
	}
	
	FVector SelfLocation = GetActorLocation();
	FVector TargetLocation = TargetToAttack->GetActorLocation();
	FVector GunDirection = TargetLocation - SelfLocation;
	//UKismetMathLibrary::RInterpTo(GunMesh->GetComponentRotation(),UKismetMathLibrary::MakeRotFromX(GunDirection),DeltaTime,5.f);
	GunMesh->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(GunDirection));
	
	FTransform FireTransform = GunMesh->GetSocketTransform(MuzzleSocketName);
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	auto Bullet = GetWorld()->SpawnActor<AProjectileBase>(BulletClass,FireTransform,Parameters);
	//auto Bullet = GetWorld()->SpawnActorDeferred<AProjectileBase>(AProjectileBase::StaticClass(),FireTransform,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (Bullet)
	{
		Bullet->ProjectileAttribute = this->TowerAttribute;
		Bullet->DamageVal = AttackDamage;
		Bullet->MovementComp->Velocity = GunDirection*5.f;
	}
}
 		

