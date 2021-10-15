#pragma once

#include "CoreMinimal.h"
#include "MilDal/Interfaces/Observer.h"
#include "MainCamera.generated.h"

UCLASS()
class MILDAL_API AMainCamera : public AActor, public IObserver
{
    GENERATED_BODY()

public:
    AMainCamera();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void Notify() override;

    float MoveSpeed;

    UPROPERTY(VisibleAnywhere)
        class UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere)
        class UCameraComponent* CameraComponent;

private:
    FVector CurrentLocation;
};
