// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveManeger.h"
#include "Kismet/GameplayStatics.h"

const FString UGameSaveManeger::SlotName = TEXT("ShootingGameSaveData");

void UGameSaveManeger::SaveGameData(int32 UserIndex, int32 NewBestScore)
{
	//저장 공간 만드는 로직
	UShootingGameSaveData* SaveGameInstance = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		//해당 슬롯 이름으로 되어있고 해당 번호인 세이브 파일이 있다.
		SaveGameInstance = Cast<UShootingGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	}

	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<UShootingGameSaveData>(UGameplayStatics::CreateSaveGameObject(UShootingGameSaveData::StaticClass()));
	}

	SaveGameInstance->BestScore = FMath::Max(SaveGameInstance->BestScore, NewBestScore); // 둘중에 더 큰 수를 반환

	//저장 로직
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
	//로컬에 세이브 데이터 있는지 확인
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		//로컬에 있는 세이브 데이터 불러오기
		UShootingGameSaveData* LoadGameInstance = Cast<UShootingGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

		//불러오는데 성공 했습니까?
		if (LoadGameInstance)
		{
			//불러오는데 성공해서 들어왔습니다.
			bSuccess = true;
			UE_LOG(LogTemp, Warning, TEXT("Save Data Load Success!"))
			//로드에 성공한 세이브 데이터 반환
			return LoadGameInstance;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("There's NO Save Data!"))
	return nullptr;
}
