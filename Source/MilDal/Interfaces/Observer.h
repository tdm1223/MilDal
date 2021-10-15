#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Observer.generated.h"

UINTERFACE(MinimalAPI)
class UObserver : public UInterface
{
    GENERATED_BODY()
};

class MILDAL_API IObserver
{
    GENERATED_BODY()

public:
    virtual void Notify() = 0;
};
