#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "MilDalPlayer.h"
#include "Kismet/GameplayStatics.h"
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
        UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(VisibleAnywhere)
        UCapsuleComponent* CapsuleComponent;

private:
    float PitchValue;
    float YawValue;
    float RollValue;
};
