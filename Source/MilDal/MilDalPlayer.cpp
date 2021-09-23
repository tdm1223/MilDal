// Fill out your copyright notice in the Description page of Project Settings.


#include "MilDalPlayer.h"
#include "MainCamera.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MilDalGameInstance.h"

AMilDalPlayer::AMilDalPlayer()
{
    JumpMaxHoldTime = 5.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f; // 점프 높이.

    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerModel(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

    if (PlayerModel.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(PlayerModel.Object);
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnimation(TEXT("AnimBlueprint'/Game/Blueprints/BP_PlayerAnim.BP_PlayerAnim_C'"));
    if (PlayerAnimation.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(PlayerAnimation.Class);
    }

    // 이동 방향과 바라보는 방향을 맞춰줌
    GetCharacterMovement()->bOrientRotationToMovement = true;
    bUseControllerRotationYaw = false;
    bIsReverse = false;


}

void AMilDalPlayer::BeginPlay()
{
    Super::BeginPlay();

    // 생성자가 아닌 BeginPlay에 추가해줘야 한다.
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMilDalPlayer::OnOverlapBegin);
}

// Called every frame
void AMilDalPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetActorLocation().Z < -100.0f)
    {
        RespawnPlayer();
    }
}

void AMilDalPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMilDalPlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMilDalPlayer::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMilDalPlayer::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMilDalPlayer::EndJump);
}

void AMilDalPlayer::MoveForward(float AxisValue)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    if (!bIsReverse)
    {
        AddMovementInput(Direction, AxisValue);
    }
    else
    {
        Direction *= -1;
        AddMovementInput(Direction, AxisValue);
    }
}

void AMilDalPlayer::MoveRight(float AxisValue)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    if (!bIsReverse)
    {
        AddMovementInput(Direction, AxisValue);
    }
    else
    {
        Direction *= -1;
        AddMovementInput(Direction, AxisValue);
    }
}

void AMilDalPlayer::StartJump()
{
    UE_LOG(LogTemp, Log, TEXT("StartJump"));
    bPressedJump = true;
}

void AMilDalPlayer::EndJump()
{
    UE_LOG(LogTemp, Log, TEXT("EndJump"));
    bPressedJump = false;
}

void AMilDalPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Camera"))
    {
        UE_LOG(LogTemp, Log, TEXT("BACK!! %s"), *OtherActor->GetName());
        SetPlayerHide(true);
        RespawnPlayer();
        SetPlayerHide(false);
    }
}

void AMilDalPlayer::SetPlayerHide(bool isHide)
{
    SetActorHiddenInGame(isHide);
    SetActorEnableCollision(!isHide);
    SetActorTickEnabled(!isHide);
}

void AMilDalPlayer::RespawnPlayer()
{
    // 현재 main 카메라의 위치를 기준으로 리스폰 위치를 정해야 한다.
    FVector cameraLocation = MilDalGameManager().GetCameraInfo();

    FVector respawnLocation = cameraLocation + AdditionalVector;

    GetCharacterMovement()->GravityScale = 0.0f;
    GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);

    FTimerHandle WaitHandle;
    GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        {
            GetCharacterMovement()->GravityScale = 1.0f;
        }), RespawnDelay, false);

    if (!this->ActorHasTag("Player1P"))
    {
        respawnLocation.Y *= -1;
    }

    Life--;
    UE_LOG(LogTemp, Log, TEXT("%s's Life : %d"), *this->GetName(), Life);
    SetActorLocation(respawnLocation);
}

void AMilDalPlayer::IncreaseLife()
{
    Life++;
}