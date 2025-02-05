// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"

void AShootingGameModeBase::AddScore(int32 Point)
{
	CurrentScore += Point;

	PrintScore();
}

void AShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidget != nullptr)
	{
		MainUI = CreateWidget<UMainWidget>(GetWorld(), MainWidget);

		if (MainUI != nullptr)
		{
			MainUI->AddToViewport();
		}
	}
}

void AShootingGameModeBase::PrintScore()
{
	if (MainUI != nullptr)
	{
		MainUI->ScoreData->SetText(FText::AsNumber(CurrentScore));
	}
}
