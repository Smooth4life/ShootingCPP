// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComp 객체화 혹은 인스턴스화
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	//BoxComp를 루트 컴포넌트로 설정
	SetRootComponent(BoxComp);

	//MeshComp를 객체화
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	//BoxComp 자식으로 설정
	MeshComp->SetupAttachment(BoxComp);

	// x = 50 y = 50 z= 50 
	FVector BoxSize = FVector(50.0f, 50.0f, 50.0f);
	BoxComp->SetBoxExtent(BoxSize);

	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(BoxComp);

	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1); //Player

	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (SubSystem != nullptr)
		{
			SubSystem->AddMappingContext(IMC_PlayerInput, 0);
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = FVector(0, Horizontal, Vertical);

	Direction.Normalize();

	FVector NewLoaction = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLoaction, true);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal);
		EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
		EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
		EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &APlayerPawn::Fire);
	}
}

void APlayerPawn::OnInputHorizontal(const FInputActionValue& value)
{
	Horizontal = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("Horizontal: %.2f"), Horizontal);
}

void APlayerPawn::OnInputVertical(const FInputActionValue& value)
{
	Vertical = value.Get<float>();
	/*UE_LOG(LogTemp, Warning, TEXT("Vertical: %.2f"), Vertical);*/
}

void APlayerPawn::Fire()
{
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletFactory, FirePosition->GetComponentLocation(), FirePosition->GetComponentRotation());

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

