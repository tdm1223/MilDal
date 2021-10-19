#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MilDalGameModeBase.generated.h"

UCLASS()
class MILDAL_API AMilDalGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMilDalGameModeBase();
    void AddItem();
    virtual void BeginPlay();
    void SpawnItem();
    void SpawnHelicopter();
    virtual void Tick(float DeltaTime);

    void ClearTimer();

    void CreateMap(FVector currentLocation);
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class AMilDalPlayer* PlyaerOne;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class AMilDalPlayer* PlayerTwo;

    TArray<TSubclassOf<class AActor>> ItemArray;
    TArray<TSubclassOf<class ATile>> TileArray;

    FTimerHandle SpawnHelicopterHandle;
    FTimerHandle SpawnItemHandle;

    UFUNCTION()
        void Notify();
};