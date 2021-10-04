#pragma once

#include "CoreMinimal.h"
#include "WindItem.generated.h"

UCLASS()
class MILDAL_API AWindItem : public AActor
{
    GENERATED_BODY()

public:
    AWindItem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    UFUNCTION()
        void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(VisibleAnywhere)
        class UCapsuleComponent* CapsuleComponent;

private:
    const float ReverseTime = 3.0f;
    float PitchValue;
    float YawValue;
    float RollValue;
};