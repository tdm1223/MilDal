// Fill out your copyright notice in the Description page of Project Settings.


#include "MilDalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMilDalPlayer::AMilDalPlayer()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

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

}

// Called to bind functionality to input
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
    AddMovementInput(Direction, AxisValue);
}

void AMilDalPlayer::MoveRight(float AxisValue)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, AxisValue);
}

void AMilDalPlayer::StartJump()
{
    bPressedJump = true;
}

void AMilDalPlayer::EndJump()
{
    bPressedJump = true;
}

void AMilDalPlayer::TestFunc()
{
    UE_LOG(LogTemp, Log, TEXT("TestFunc"));
}

void AMilDalPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Camera"))
    {
        UE_LOG(LogTemp, Log, TEXT("BACK!! %s"), *OtherActor->GetName());
        SetPlayerVisibility(true);
    }
}

void AMilDalPlayer::SetPlayerVisibility(bool isHide)
{
    SetActorHiddenInGame(isHide);
    SetActorEnableCollision(!isHide);
    SetActorTickEnabled(!isHide);
}