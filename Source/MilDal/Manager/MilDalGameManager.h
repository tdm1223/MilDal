#pragma once

#include "CoreMinimal.h"
#include "MilDalGameManager.generated.h"

class AMilDalPlayer;
class AMainCamera;
class UMainWidget;
class AMilDalPlayerController;

enum PlayerType
{
    PlayerOne,
    PlayerTwo,
};

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
};
