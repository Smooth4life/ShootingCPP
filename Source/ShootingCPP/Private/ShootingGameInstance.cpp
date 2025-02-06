// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameInstance.h"

void UShootingGameInstance::Init()
{
    Super::Init();

    if (!SaveMagager) // SaveManager == nullptr
    {
        SaveMagager = NewObject<UGameSaveManeger>(this);
        SaveMagager->AddToRoot(); //GC 수거하는걸 막아줌
    }

}

void UShootingGameInstance::Shutdown()
{
    Super::Shutdown();
    
    if (SaveMagager)
    {
        SaveMagager->RemoveFromRoot();
        SaveMagager = nullptr;

    }
}

UGameSaveManeger* UShootingGameInstance::GetSaveGameManager()
{
    return SaveMagager;
}
