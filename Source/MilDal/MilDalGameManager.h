#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MilDalGameManager.generated.h"

class AMilDalPlayer;
class AMainCamera;
class UMainWidget;
class AMilDalPlayerController;

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

    void SetReverse(bool bReverse, bool bIsPlayerOne);
    void RegisterPlayer(AMilDalPlayer* player, bool bIsPlayerOne);
    void RegisterController();
    class UMainWidget* GetMainwWidget() const;

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
