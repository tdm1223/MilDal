#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MilDalPlayer.generated.h"

UCLASS()
class MILDAL_API AMilDalPlayer : public ACharacter
{
    GENERATED_BODY()

public:
    AMilDalPlayer();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void StartJump();
    void EndJump();

    UFUNCTION()
        void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void SetPlayerHide(bool isHide);
    void RespawnPlayer();
    void IncreaseLife();

    UPROPERTY(EditAnywhere)
        TSubclassOf<class AMainCamera> MainCamera;

    UPROPERTY(VisibleAnywhere)
        class UTextRenderComponent* NameText;

    void SetReverse(bool reverse)
    {
        bIsReverse = reverse;
    }

    void SetInfiniteJump(bool bJump)
    {
        if (bJump)
        {
            JumpMaxCount = 100;
        }
        else
        {
            JumpMaxCount = 1;
        }
    }

    void SetFast(bool fast)
    {
        bIsFast = fast;
    }

    UPROPERTY(BlueprintReadOnly)
        bool bIsReverse = false;

    UPROPERTY(BlueprintReadOnly)
        bool bIsFast = false;

    UPROPERTY(VisibleAnywhere)
        class UCharacterStatComponent* characterStatComponent;

private:
    float RespawnDelay = 2.0f;
    FVector AdditionalVector = FVector(400.0f, 0.0f, -100.0f);
};
