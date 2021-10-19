#include "MilDalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"

#include "MilDal/Actors/MainCamera.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/Player/CharacterStatComponent.h"
#include "MilDal/UI/MainWidget.h"
#include "MilDal/MilDal.h"

AMilDalPlayer::AMilDalPlayer()
{
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerModel(TEXT("SkeletalMesh'/Game/Character/Mesh/Monkey_Mesh.Monkey_Mesh'"));

    if (PlayerModel.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(PlayerModel.Object);
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
        GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
    }

    GetCapsuleComponent()->SetCapsuleHalfHeight(68.0f);
    GetCapsuleComponent()->SetCapsuleRadius(28.0f);
    static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnimation(TEXT("AnimBlueprint'/Game/Animations/BP_PlayerAnim.BP_PlayerAnim_C'"));
    if (PlayerAnimation.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(PlayerAnimation.Class);
    }
    GetMesh()->CastShadow = false;

    // 이동 방향과 바라보는 방향을 맞춰줌
    GetCharacterMovement()->bOrientRotationToMovement = true;
    bUseControllerRotationYaw = false;
    bIsReverse = false;
    bIsFast = false;

    NameText = CreateDefaultSubobject<UTextRenderComponent>("PlayerName");
    NameText->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
    NameText->SetUsingAbsoluteRotation(true);
    NameText->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
    NameText->SetTextRenderColor(FColor::Red);
    NameText->SetupAttachment(RootComponent);

    this->characterStatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("PlayerStat"));

    PushCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PushCollision"));
    PushCollision->SetCapsuleHalfHeight(30.0f);
    PushCollision->SetCapsuleRadius(30.0f);
    PushCollision->SetupAttachment(RootComponent);
}

void AMilDalPlayer::BeginPlay()
{
    Super::BeginPlay();

    // 생성자가 아닌 BeginPlay에 추가해줘야 한다.
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMilDalPlayer::OnOverlapBegin);
    PushCollision->OnComponentBeginOverlap.AddDynamic(this, &AMilDalPlayer::OnPushBegin);

    if (this->ActorHasTag("Player2P"))
    {
        MilDalGameManager().RegistPlayer(this, PlayerType::PlayerTwo);
    }
    else
    {
        MilDalGameManager().RegistPlayer(this, PlayerType::PlayerOne);
        MilDalGameManager().RegistController();
    }
    NameText->SetText(FText::FromString(characterStatComponent->GetName()));
}

void AMilDalPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetActorLocation().Z < -100.0f)
    {
        RespawnPlayer();
    }

    if (bIsFast)
    {
        AddMovementInput(FVector(1.0f, 0.0f, 0.0f), 5.0f);
    }

    if (bPlayerTwoReady)
    {
        MilDalGameManager().SetPlayerTwoIsReady(true);
    }

    if (GetCharacterMovement()->GravityScale == 0)
    {
        if (bSetBlink)
        {
            GetMesh()->SetVisibility(false);
            bSetBlink = false;
        }
        else
        {
            GetMesh()->SetVisibility(true);
            bSetBlink = true;
        }
    }
    else
    {
        GetMesh()->SetVisibility(true);
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
    if (!CheckMovable())
    {
        return;
    }

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
    if (!CheckMovable())
    {
        return;
    }

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
    if (MilDalGameManager().GetPlayerOneIsReady() == false)
    {
        MilDalGameManager().SetPlayerOneIsReady(true);
        bPlayerOneReady = true;
    }

    bPressedJump = true;
    GetCharacterMovement()->GravityScale = 1.0f;
}

void AMilDalPlayer::EndJump()
{
    bPressedJump = false;
}

void AMilDalPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Camera"))
    {
        SetPlayerHide(true);
        RespawnPlayer();
        SetPlayerHide(false);
    }
}

void AMilDalPlayer::OnPushBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Player1P"))
    {
        if (GetCharacterMovement()->IsMovingOnGround())
        {
            FVector pushVector = (OtherActor->GetActorLocation() - this->GetActorLocation()) * 5.0f;
            pushVector.Z = 80.0f;
            Cast<AMilDalPlayer>(OtherActor)->GetCharacterMovement()->AddImpulse(pushVector, true);
        }
    }

    if (OtherActor->ActorHasTag("Player2P"))
    {
        if (GetCharacterMovement()->IsMovingOnGround())
        {
            FVector pushVector = (OtherActor->GetActorLocation() - this->GetActorLocation()) * 5.0f;
            pushVector.Z = 80.0f;
            Cast<AMilDalPlayer>(OtherActor)->GetCharacterMovement()->AddImpulse(pushVector, true);
        }
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
    bSetBlink = true;

    // 현재 main 카메라의 위치를 기준으로 리스폰 위치를 정해야 한다.
    FVector cameraLocation = MilDalGameManager().GetCameraInfo();

    FVector respawnLocation = cameraLocation + AdditionalVector;

    GetCharacterMovement()->GravityScale = 0.0f;
    GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);

    FTimerHandle WaitHandle;
    GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        {
            bSetBlink = false;
            GetCharacterMovement()->GravityScale = 1.0f;
        }), RespawnDelay, false);

    if (!this->ActorHasTag("Player1P"))
    {
        respawnLocation.Y *= -1;
    }

    characterStatComponent->DecreaseLife();
    if (characterStatComponent->GetLife() == 0 && MilDalGameManager().GetIsGameEnd() == false)
    {
        MD_LOG(Warning, TEXT("%s GameOver"), *characterStatComponent->GetName());
        SetPlayerHide(true);
        MilDalGameManager().NotifyGameOver();
    }
    else
    {
        SetActorLocation(respawnLocation);
    }
}

void AMilDalPlayer::IncreaseLife()
{
    characterStatComponent->IncreaseLife();
}

bool AMilDalPlayer::CheckMovable()
{
    if (MilDalGameManager().GetPlayerOneIsReady()
        && MilDalGameManager().GetPlayerTwoIsReady()
        && MilDalGameManager().GetIsGameStart())
    {
        bPlayerMovable = true;
        return true;
    }
    return false;
}