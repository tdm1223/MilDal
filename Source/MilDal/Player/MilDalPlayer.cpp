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
}

void AMilDalPlayer::BeginPlay()
{
    Super::BeginPlay();

    // 생성자가 아닌 BeginPlay에 추가해줘야 한다.
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMilDalPlayer::OnOverlapBegin);

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

// Called every frame
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
    bPressedJump = true;
}

void AMilDalPlayer::EndJump()
{
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

    characterStatComponent->DecreaseLife();
    UE_LOG(LogTemp, Log, TEXT("%s's Life : %d"), *this->GetName(), characterStatComponent->Life);
    SetActorLocation(respawnLocation);
}

void AMilDalPlayer::IncreaseLife()
{
    characterStatComponent->IncreaseLife();
}