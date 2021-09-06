#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCamera.generated.h"

/**
 *
 */
UCLASS()
class MILDAL_API AMainCamera : public ACameraActor
{
    GENERATED_BODY()

public:
    AMainCamera();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);

    // ToDo : 적절한 스피드를 찾은 후에는 내부 변수로 넣어야 한다.
    UPROPERTY(EditAnywhere)
    float MoveSpeed;

private:
    FVector CurrentLocation;
};
