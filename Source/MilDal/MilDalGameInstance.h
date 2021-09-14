// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MilDalGameManager.h"
#include "MilDalGameInstance.generated.h"

UCLASS()
class MILDAL_API UMilDalGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    static UMilDalGameInstance* GetInstance();

    UPROPERTY(VisibleAnywhere)
    UMilDalGameManager* MilDalGameManager = nullptr;

    virtual void Init() override;

    void GenerateManager();

    UMilDalGameManager* GetMilDalGameManager();

private:
    static UMilDalGameInstance* Instance;
};

inline UMilDalGameManager& MilDalGameManager()
{
    return *UMilDalGameInstance::GetInstance()->GetMilDalGameManager();
}
