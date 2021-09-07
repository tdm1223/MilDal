// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainCamera.h"
#include "MilDalGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class MILDAL_API AMilDalGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMilDalGameModeBase();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
};