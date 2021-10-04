#pragma once

#include "CoreMinimal.h"
#include "LifeItem.generated.h"

UCLASS()
class MILDAL_API ALifeItem : public AActor
{
    GENERATED_BODY()

public:
    ALifeItem();

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
    float PitchValue;
    float YawValue;
    float RollValue;
};
