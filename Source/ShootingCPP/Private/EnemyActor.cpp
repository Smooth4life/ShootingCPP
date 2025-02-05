// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComp->SetupAttachment(BoxComp);

	BoxComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	int32 DrawResult = FMath::RandRange(1, 100);
	
	if (DrawResult <= TraceRate)
	{
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			if (player->GetName().Contains(TEXT("BP_PlayerPawn")))
			{
				Direction = player->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
			}
		}
	}
	else
	{
		Direction = GetActorForwardVector();
	}

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemytOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AEnemyActor::OnEnemytOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

	if (Player != nullptr)
	{
		//Player가 정상적으로 형변환 되면 들어오게 된다.
		OtherActor->Destroy();
	}

	Destroy();
}

