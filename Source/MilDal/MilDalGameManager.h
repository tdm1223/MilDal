#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MainCamera.h"
#include "MilDalPlayer.h"
#include "MilDalGameManager.generated.h"

UCLASS()
class MILDAL_API UMilDalGameManager : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<class AMainCamera> FindClassType;

public:
    UMilDalGameManager();
    FVector GetCameraInfo();

    void SetReverse(bool bReverse, bool bIsPlayerOne);
    void RegisterPlayer(AMilDalPlayer* player, bool bIsPlayerOne);

    UPROPERTY(EditAnywhere)
        AMainCamera* MainCamera;

    UPROPERTY(VisibleAnywhere)
        AMilDalPlayer* PlayerOne;

    UPROPERTY(VisibleAnywhere)
        AMilDalPlayer* PlayerTwo;
};
