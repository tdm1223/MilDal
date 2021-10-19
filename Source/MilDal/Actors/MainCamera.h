#pragma once

#include "CoreMinimal.h"
#include "MainCamera.generated.h"

UCLASS()
class MILDAL_API AMainCamera : public AActor
{
    GENERATED_BODY()

public:
    AMainCamera();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    float MoveSpeed;

    UPROPERTY(VisibleAnywhere)
        class UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere)
        class UCameraComponent* CameraComponent;

    UFUNCTION()
        void Notify();

private:
    FVector CurrentLocation;
};
