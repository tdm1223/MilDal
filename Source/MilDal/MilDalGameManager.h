#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MilDalGameManager.generated.h"

UCLASS()
class MILDAL_API UMilDalGameManager : public UObject
{
    GENERATED_BODY()

public:
    void GetCameraInfo();
};
