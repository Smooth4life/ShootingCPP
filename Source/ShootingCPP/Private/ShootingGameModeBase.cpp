// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "ManuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingGameInstance.h"

void AShootingGameModeBase::AddScore(int32 Point)
{
	CurrentScore += Point;

	PrintScore();
}

void AShootingGameModeBase::ShowMenu()
{
	if (MenuWidget != nullptr)
	{
		MenuUI = CreateWidget<UManuWidget>(GetWorld(), MenuWidget);

		if (MenuUI != nullptr)
		{
			MenuUI->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);

			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
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
		MainUI->BestScoreData->SetText(FText::AsNumber(BestScore));
	}
}

void AShootingGameModeBase::LoadBestScore()
{

}

void AShootingGameModeBase::SaveBestScore()
{

}
