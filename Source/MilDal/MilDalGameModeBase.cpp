// Copyright Epic Games, Inc. All Rights Reserved.


#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerOne.h"

AMilDalGameModeBase::AMilDalGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
    DefaultPawnClass = APlayerOne::StaticClass();
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