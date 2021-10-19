#pragma once

#include "CoreMinimal.h"
#include "MilDalGameManager.generated.h"

class AMilDalPlayer;
class AMainCamera;
class UMainWidget;
class AMilDalPlayerController;
class AMilDalGameModeBase;

enum PlayerType
{
    PlayerOne,
    PlayerTwo,
};

DECLARE_MULTICAST_DELEGATE(FGameEndSignature);

UCLASS()
class MILDAL_API UMilDalGameManager : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<AMainCamera> FindClassType;

public:
    UMilDalGameManager();
    FVector GetCameraInfo();

    void SetMainCamera();

    void SetReverse(bool bReverse, PlayerType InEatPlayer);
    void SetInfiniteJump(bool bReverse, PlayerType InEatPlayer);
    void SetFast(bool bFast, PlayerType InEatPlayer);

    void RegistPlayer(AMilDalPlayer* player, PlayerType InCurrentPlayer);
    void RegistController();
    UMainWidget* GetMainwWidget() const;

    UFUNCTION()
        void NotifyGameOver();

    FGameEndSignature GameEndDelegate;

    UPROPERTY(EditAnywhere)
        AMainCamera* MainCamera;

    UPROPERTY(VisibleAnywhere)
        AMilDalPlayer* PlayerOne;

    UPROPERTY(VisibleAnywhere)
        AMilDalPlayer* PlayerTwo;

    UPROPERTY(VisibleAnywhere)
        UMainWidget* MainWidget;

    UPROPERTY()
        AMilDalPlayerController* controller;

    UPROPERTY()
        AMilDalGameModeBase* mode;

    bool GetPlayerOneIsReady()
    {
        return bPlayerOneIsReady;
    }

    void SetPlayerOneIsReady(bool InIsReady)
    {
        bPlayerOneIsReady = InIsReady;
    }

    bool GetPlayerTwoIsReady()
    {
        return bPlayerTwoIsReady;
    }

    void SetPlayerTwoIsReady(bool InIsReady)
    {
        bPlayerTwoIsReady = InIsReady;
    }

    bool GetIsGameEnd()
    {
        return bIsGameEnd;
    }

    void SetIsGameEnd(bool InIsEnd)
    {
        bIsGameEnd = InIsEnd;
    }

    bool GetIsGameStart()
    {
        return bIsGameStart;
    }

    void SetIsGameStart(bool InIsStart)
    {
        bIsGameStart = InIsStart;
    }

private:
    bool bPlayerOneIsReady;
    bool bPlayerTwoIsReady;
    bool bIsGameEnd;
    bool bIsGameStart;
};
