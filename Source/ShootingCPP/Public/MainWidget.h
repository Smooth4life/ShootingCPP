// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UTextBlock* ScoreData;
};
