// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddScore(int32 Point);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidget;

protected:
	virtual void BeginPlay() override;


private:
	int32 CurrentScore = 0;

	class UMainWidget* MainUI;

	void PrintScore();
	
};
