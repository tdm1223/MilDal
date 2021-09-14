// Fill out your copyright notice in the Description page of Project Settings.


#include "MilDalGameInstance.h"
#include "MilDalGameManager.h"

UMilDalGameInstance* UMilDalGameInstance::Instance = nullptr;

UMilDalGameInstance* UMilDalGameInstance::GetInstance()
{
    return UMilDalGameInstance::Instance;
}

void UMilDalGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Log, TEXT("UMilDalGameInstance Init"));

    UMilDalGameInstance::Instance = this;

    GenerateManager();
}

void UMilDalGameInstance::GenerateManager()
{
    if (!MilDalGameManager)
    {
        UE_LOG(LogTemp, Log, TEXT("UMilDalGameManager Generate"));
        MilDalGameManager = NewObject<UMilDalGameManager>(this, UMilDalGameManager::StaticClass());
    }
}

UMilDalGameManager* UMilDalGameInstance::GetMilDalGameManager()
{
    return MilDalGameManager;
}