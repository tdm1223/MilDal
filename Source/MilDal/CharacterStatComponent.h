#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MILDAL_API UCharacterStatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterStatComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    int GetLife()
    {
        return Life;
    }

    int GetSpeed()
    {
        return Speed;
    }

    FString GetName()
    {
        return Name;
    }

    UPROPERTY(VisibleAnywhere)
        int Life;

    UPROPERTY(VisibleAnywhere)
        float Speed;

    UPROPERTY(VisibleAnywhere)
        FString Name;

    UFUNCTION()
        void IncreaseLife();

    UFUNCTION()
        void DecreaseLife();
};

