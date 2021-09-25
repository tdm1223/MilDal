// Copyright Epic Games, Inc. All Rights Reserved.


#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
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

}

void AMilDalGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Log, TEXT("Log Message2"));
}