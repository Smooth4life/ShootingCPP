// Fill out your copyright notice in the Description page of Project Settings.


#include "ManuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UManuWidget::NativeConstruct()
{
	ButtonRestart->OnClicked.AddDynamic(this, &UManuWidget::Restart);
	ButtonQuit->OnClicked.AddDynamic(this, &UManuWidget::Quit);
}

void UManuWidget::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void UManuWidget::Quit()
{
	UWorld* CurrentWorld = GetWorld();
	UKismetSystemLibrary::QuitGame(CurrentWorld, CurrentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
