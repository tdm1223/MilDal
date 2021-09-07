// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
    PrimaryActorTick.bCanEverTick = true;

    //static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerModel(TEXT("SkeletalMesh'/Game/Character/Monkey_Mesh.Monkey_Mesh'"));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerModel(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
    if (PlayerModel.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(PlayerModel.Object);
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnimation(TEXT("AnimBlueprint'/Game/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
    if (PlayerAnimation.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(PlayerAnimation.Class);
    }

    // 이동 방향과 바라보는 방향을 맞춰줌
    GetCharacterMovement()->bOrientRotationToMovement = true;
    bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasicPlayer::MoveForward(float AxisValue)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, AxisValue);
}

void ABasicPlayer::MoveRight(float AxisValue)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, AxisValue);
}

void ABasicPlayer::StartJump()
{
    bPressedJump = true;
}

void ABasicPlayer::EndJump()
{
    bPressedJump = true;
}