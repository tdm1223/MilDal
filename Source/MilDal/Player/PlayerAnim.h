#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UCLASS()
class MILDAL_API UPlayerAnim : public UAnimInstance
{
    GENERATED_BODY()

public:
    UPlayerAnim();
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        float Speed;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        bool bIsJump;

private:
    ACharacter* Character;
};
