// Copyright Epic Games, Inc. All Rights Reserved.


#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Helicopter.h"
#include "MilDalGameInstance.h"
#include "MilDalPlayerController.h"
#include "MilDalPlayer.h"

AMilDalGameModeBase::AMilDalGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;

    ConstructorHelpers::FClassFinder<APawn> player(*FString(TEXT("Blueprint'/Game/Blueprints/BP_PlayerOne.BP_PlayerOne_C'")));

    if (player.Succeeded())
    {
        DefaultPawnClass = player.Class;
    }

    PlayerControllerClass = AMilDalPlayerController::StaticClass();
}

void AMilDalGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    SpawnHelicopter();
}

void AMilDalGameModeBase::SpawnHelicopter()
{
    FTimerHandle WaitHandle;

    bool flag = FMath::RandBool();
    UE_LOG(LogTemp, Log, TEXT("flag : %d"), flag);
    FTransform SpawnLocation;

    FVector AdditionalVector = FVector(1000.0f, 1000.0f, -380.0f);
    if (flag)
    {
        AdditionalVector.Y *= -1;
        SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 180.0f, 0.0f)));
    }
    SpawnLocation.SetLocation(MilDalGameManager().GetCameraInfo() + AdditionalVector);

    GetWorld()->SpawnActor<AHelicopter>(AHelicopter::StaticClass(), SpawnLocation);

    float randomTime = FMath::RandHelper(5) + 3;
    GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        {
            SpawnHelicopter();
        }), randomTime, false);
}

void AMilDalGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}