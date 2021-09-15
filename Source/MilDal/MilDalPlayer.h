// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "MilDalPlayer.generated.h"

UCLASS()
class MILDAL_API AMilDalPlayer : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AMilDalPlayer();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void StartJump();
    void EndJump();

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere)
    int Life = 5;

    void SetPlayerHide(bool isHide);
    void RespawnPlayer();

    void IncreaseLife();

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AMainCamera> MainCamera;

    bool GetReverse()
    {
        return bIsReverse;
    }

    void SetReverse(bool reverse)
    {
        bIsReverse = reverse;
    }

private:
    bool bIsReverse = false;
    float RespawnDelay = 2.0f;
    FVector AdditionalVector = FVector(400.0f, 0.0f, -100.0f);
};
