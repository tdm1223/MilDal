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

    // ToDo : 적절한 스피드를 찾은 후에는 내부 변수로 넣어야 한다.
    UPROPERTY(EditAnywhere)
        float MoveSpeed;

    UPROPERTY(VisibleAnywhere)
        class UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere)
        class UCameraComponent* CameraComponent;

private:
    FVector CurrentLocation;
};
