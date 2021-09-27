#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "WindObstacle.generated.h"

UCLASS()
class MILDAL_API AWindObstacle : public AActor
{
    GENERATED_BODY()

public:
    AWindObstacle();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        class UArrowComponent* Arrow = nullptr;

    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* LeftObstacle = nullptr;

    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* RightObstacle = nullptr;

    FVector LeftLocation = GetActorLocation();
    FVector RightLocation = GetActorLocation();

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        float MoveSpeed = 7.0f;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
        float SpawnTime = 1.7f;
};
