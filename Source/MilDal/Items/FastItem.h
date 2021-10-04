#pragma once

#include "CoreMinimal.h"
#include "MilDal/Interfaces/ItemInterface.h"
#include "FastItem.generated.h"

UCLASS()
class MILDAL_API AFastItem : public AActor, public IItemInterface
{
    GENERATED_BODY()

public:
    AFastItem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(VisibleAnywhere)
        class UCapsuleComponent* CapsuleComponent;

    UFUNCTION()
        void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
