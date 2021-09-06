// Copyright Epic Games, Inc. All Rights Reserved.


#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMilDalGameModeBase::AMilDalGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMilDalGameModeBase::BeginPlay()
{
    Super::BeginPlay();

}

void AMilDalGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //UE_LOG(LogTemp, Log, TEXT("Log Message2"));
}