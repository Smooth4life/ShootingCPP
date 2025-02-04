// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTestActor.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Number1 = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Number2 = 3.14f;

	UPROPERTY(EditInstanceOnly)
	FString name = TEXT("민기");

	//반환값 함수이름(뭘 받을것인지, 뭘 받을것인지);
	UFUNCTION(BlueprintPure)
	int32 Add(int32 A, int32 B);
};
