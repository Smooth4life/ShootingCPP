// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShootingGameSaveData.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UShootingGameSaveData : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere, Category="Save Data")
	int32 BestScore;

};
