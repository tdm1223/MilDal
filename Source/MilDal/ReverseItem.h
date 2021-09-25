#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "MilDalGameInstance.h"
#include "ReverseItem.generated.h"

UCLASS()
class MILDAL_API AReverseItem : public AActor
{
    GENERATED_BODY()

public:
    AReverseItem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
        void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(VisibleAnywhere)
        UCapsuleComponent* CapsuleComponent;

private:
    const float ReverseTime = 3.0f;
    float PitchValue;
    float YawValue;
    float RollValue;
};
