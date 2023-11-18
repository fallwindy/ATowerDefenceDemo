
#include "ProjectileBase.h"
#include "EnemyBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	OutCollision = CreateDefaultSubobject<USphereComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;
	OutCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OutCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	OutCollision->SetGenerateOverlapEvents(true);
	OutCollision->OnComponentBeginOverlap.AddDynamic(this,&AProjectileBase::OnOverlap);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementCmop"));
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->InitialSpeed = 30000.f;

	InitialLifeSpan = 5.f;
}


void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}


void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttributeColor==FVector(0,0,0))
	{
		switch (ProjectileAttribute)
		{
			case Normal:
				{
					AttributeColor = FVector(1,1,1);
					break;
				}
			case Fire:
				{
					AttributeColor = FVector(1,0,0);
					break;
				}
			case Ice:
				{
					AttributeColor = FVector(0,0,1);
					break;
				}
			default:
				break;
		}
		Mesh->SetVectorParameterValueOnMaterials(FName("Color"),AttributeColor);
	}

}

void AProjectileBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AEnemyBase>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor,DamageVal,UGameplayStatics::GetPlayerController(GetWorld(),0),this,DamagTypeClass);
	}
	Destroy();
	return;
}

