// Copyright Epic Games, Inc. All Rights Reserved.


#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "GameFramework/PlayerController.h"

AMilDalGameModeBase::AMilDalGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
    //DefaultPawnClass = APlayerOne::StaticClass();
    //DefaultPawnClass = NULL;
}

void AMilDalGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    //UGameplayStatics::GetAllActorsWithTag(this, FName("Player"), OutActors);
    //for (auto Controller : OutActors)
    //{
    //    UE_LOG(LogTemp, Log, TEXT("%s"), *Controller->GetOwner()->GetName());
    //}

    FVector location1(-250.0f, 250.0f, 200.0f);
    FVector location2(-250.0f, -250.0f, 200.0f);

    auto controller1 = UGameplayStatics::CreatePlayer(APlayerOne::StaticClass(), 0, true);
    auto controller2 = UGameplayStatics::CreatePlayer(APlayerTwo::StaticClass(), 1, true);

    //UGameplayStatics::GetPlayerController(APlayerOne::StaticClass(), 0);
    //UGameplayStatics::GetPlayerController(APlayerTwo::StaticClass(), 1)->OnPossess()

    //UGameplayStatics::CreatePlayer(APlayerTwo::StaticClass(), 1, true);


}

void AMilDalGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Log, TEXT("Log Message2"));
}

void AMilDalGameModeBase::GetPlayerStartPoints()
{
    UGameplayStatics::GetAllActorsWithTag(this, FName("Player"), OutActors);
    //UGameplayStatics::GetAllActorsOfClass(NULL, NULL, PlayerStartArray);
}