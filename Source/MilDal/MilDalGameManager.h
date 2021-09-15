#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MainCamera.h"
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

    UPROPERTY(EditAnywhere)
    AMainCamera* MainCamera;
};
