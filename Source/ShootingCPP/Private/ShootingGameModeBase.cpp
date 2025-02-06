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

	if (CurrentScore > BestScore)
	{
		BestScore = CurrentScore;
		SaveBestScore();
	}

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

	LoadBestScore();

	if (MainWidget != nullptr)
	{
		MainUI = CreateWidget<UMainWidget>(GetWorld(), MainWidget);

		if (MainUI != nullptr)
		{
			MainUI->AddToViewport();
		}
	}

	PrintScore();
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
	bool bSuccess = false;
	UShootingGameInstance* ShootingGameInstance = Cast<UShootingGameInstance>(GetGameInstance());
	if (ShootingGameInstance)
	{
		UGameSaveManeger* SaveManager = ShootingGameInstance->GetSaveGameManager();
		if (SaveManager)
		{
			UShootingGameSaveData* SaveData = SaveManager->LoadGameInstance(0, bSuccess);
			if (bSuccess && SaveData)
			{
				BestScore = SaveData->BestScore;
				UE_LOG(LogTemp, Warning, TEXT("Loaded Best Scor : %d"), BestScore);
			}
		}
	}
}

void AShootingGameModeBase::SaveBestScore()
{
	UShootingGameInstance* GameInstance = Cast<UShootingGameInstance>(GetGameInstance());

	if (GameInstance) 
	{
		UGameSaveManeger* SaveManager = GameInstance->GetSaveGameManager();
		if (SaveManager)
		{
			SaveManager->SaveGameData(0, BestScore);
			UE_LOG(LogTemp, Warning, TEXT("New Best Score Saved : %d"), BestScore);
		}
	}
}
