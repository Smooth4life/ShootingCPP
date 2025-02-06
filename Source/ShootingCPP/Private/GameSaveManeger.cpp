// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveManeger.h"
#include "Kismet/GameplayStatics.h"

const FString UGameSaveManeger::SlotName = TEXT("ShootingGameSaveData");

void UGameSaveManeger::SaveGameData(int32 UserIndex, int32 NewBestScore)
{
	//���� ���� ����� ����
	UShootingGameSaveData* SaveGameInstance = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		//�ش� ���� �̸����� �Ǿ��ְ� �ش� ��ȣ�� ���̺� ������ �ִ�.
		SaveGameInstance = Cast<UShootingGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	}

	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<UShootingGameSaveData>(UGameplayStatics::CreateSaveGameObject(UShootingGameSaveData::StaticClass()));
	}

	SaveGameInstance->BestScore = FMath::Max(SaveGameInstance->BestScore, NewBestScore); // ���߿� �� ū ���� ��ȯ

	//���� ����
	if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Best Score Save Success!"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Save Failed Error!"))
	}
}

UShootingGameSaveData* UGameSaveManeger::LoadGameInstance(int32 UserIndex, bool& bSuccess)
{
	//���ÿ� ���̺� ������ �ִ��� Ȯ��
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		//���ÿ� �ִ� ���̺� ������ �ҷ�����
		UShootingGameSaveData* LoadGameInstance = Cast<UShootingGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

		//�ҷ����µ� ���� �߽��ϱ�?
		if (LoadGameInstance)
		{
			//�ҷ����µ� �����ؼ� ���Խ��ϴ�.
			bSuccess = true;
			UE_LOG(LogTemp, Warning, TEXT("Save Data Load Success!"))
			//�ε忡 ������ ���̺� ������ ��ȯ
			return LoadGameInstance;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("There's NO Save Data!"))
	return nullptr;
}
