#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Helicopter.generated.h"

UCLASS()
class MILDAL_API AHelicopter : public AActor
{
    GENERATED_BODY()

public:
    AHelicopter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        class UArrowComponent* Arrow = nullptr;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        UStaticMeshComponent* Body = nullptr;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        UStaticMeshComponent* Motor = nullptr;

    FVector BodyLocation = GetActorLocation();
    FVector MotorLocation = GetActorLocation();
    float MoveSpeed = 5.0f;
private:
    float YawValue;
};
