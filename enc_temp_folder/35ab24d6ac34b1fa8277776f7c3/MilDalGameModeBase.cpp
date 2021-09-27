// Copyright Epic Games, Inc. All Rights Reserved.


#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Helicopter.h"
#include "MilDalGameInstance.h"
#include "MilDalPlayer.h"

AMilDalGameModeBase::AMilDalGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;

    ConstructorHelpers::FClassFinder<APawn> player(*FString(TEXT("Blueprint'/Game/Blueprints/BP_PlayerOne.BP_PlayerOne_C'")));

    if (player.Succeeded())
    {
        DefaultPawnClass = player.Class;
    }
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

    FVector AdditionalVector = FVector(1000.0f, 1000.0f, -380.0f);
    if (flag)
    {
        AdditionalVector.Y *= -1;
    }
    FTransform SpawnLocation;
    SpawnLocation.SetLocation(MilDalGameManager().GetCameraInfo() + AdditionalVector);
    GetWorld()->SpawnActor<AHelicopter>(AHelicopter::StaticClass(), SpawnLocation);



    //float randomTime = FMath::RandHelper(5) + 3;
    float randomTime = 2;
    UE_LOG(LogTemp, Log, TEXT("RANDOM! %f"), randomTime);
    GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        {
            SpawnHelicopter();
        }), randomTime, false);
}

void AMilDalGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}