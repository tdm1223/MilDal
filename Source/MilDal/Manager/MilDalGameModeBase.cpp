#include "MilDalGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MilDal/Actors/Helicopter.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/Player/MilDalPlayerController.h"
#include "MilDal/Player/MilDalPlayer.h"

// Item
#include "MilDal/Items/ReverseItem.h"
#include "MilDal/Items/FastItem.h"
#include "MilDal/Items/InfiniteJumpItem.h"
#include "MilDal/Items/LifeItem.h"
#include "MilDal/Items/WindItem.h"

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

    ItemArray.Add(AFastItem::StaticClass());
    ItemArray.Add(AReverseItem::StaticClass());
    ItemArray.Add(AInfiniteJumpItem::StaticClass());
    ItemArray.Add(ALifeItem::StaticClass());
    ItemArray.Add(AWindItem::StaticClass());

    SpawnItem();
}

void AMilDalGameModeBase::SpawnItem()
{
    FTimerHandle WaitHandle;

    FTransform SpawnLocation;

    float randomXPosition = FMath::RandRange(400, 1200);
    float randomYPosition = FMath::RandRange(-400, 400);
    FVector AdditionalVector = FVector(randomXPosition, randomYPosition, -380.0f);
    SpawnLocation.SetLocation(MilDalGameManager().GetCameraInfo() + AdditionalVector);

    int randomIndex = FMath::RandHelper(ItemArray.Num());
    GetWorld()->SpawnActor<AActor>(ItemArray[randomIndex], SpawnLocation);

    float randomTime = FMath::RandHelper(1) + 3;
    GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        {
            SpawnItem();
        }), randomTime, false);
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