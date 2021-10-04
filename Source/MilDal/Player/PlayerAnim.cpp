#include "PlayerAnim.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnim::UPlayerAnim()
{
    bIsJump = false;
}

void UPlayerAnim::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    APawn* Pawn = TryGetPawnOwner();
    if (::IsValid(Pawn))
    {
        Character = Cast<ACharacter>(Pawn);
    }
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (Character == nullptr)
    {
        return;
    }

    Speed = Character->GetVelocity().Size();
    bIsJump = Character->GetCharacterMovement()->IsFalling();
}