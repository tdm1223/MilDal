#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
    GENERATED_BODY()
};

class MILDAL_API IItemInterface
{
    GENERATED_BODY()

public:
    const float Duration = 2.0f;
    float PitchValue;
    float YawValue;
    float RollValue;
};
