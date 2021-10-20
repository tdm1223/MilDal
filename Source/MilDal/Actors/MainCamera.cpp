#include "MainCamera.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/MilDal.h"
#include "Components/TextRenderComponent.h"

AMainCamera::AMainCamera()
{
    PrimaryActorTick.bCanEverTick = true;
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    CameraComponent->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
    RootComponent = CameraComponent;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OutTrigger"));
    BoxComponent->SetupAttachment(RootComponent);
    BoxComponent->SetRelativeLocation(FVector(390.0f, 0.0f, -600.0f));
    BoxComponent->SetRelativeRotation(FRotator(40.0f, 0.0f, 0.0f));
    BoxComponent->SetBoxExtent(FVector(32.0f, 1280.0f, 640.0f));

    CameraText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Countdown Text"));
    CameraText->SetHorizontalAlignment(EHTA_Center);
    CameraText->SetWorldSize(100.0f);
    CameraText->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
    CameraText->SetText(TEXT("PRESS JUMP TO READY"));
    CameraText->SetTextRenderColor(FColor::Red);
    CountdownTime = 3;
    Tags.Add("Camera");
    bTimerStart = false;
}

void AMainCamera::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->SetViewTargetWithBlend(this);
    }
    CurrentLocation = this->GetActorLocation();

    MoveSpeed = 0;
    bTimerStart = false;

    // Delegate 등록
    MilDalGameManager().GameEndDelegate.AddUObject(this, &AMainCamera::Notify);
}

void AMainCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 1P 2P 모두 Ready 라면
    if (MilDalGameManager().GetPlayerOneIsReady() && MilDalGameManager().GetPlayerTwoIsReady())
    {
        // 게임이 시작된게 아니라면 게임 스타트 플래그 실행
        if (!MilDalGameManager().GetIsGameStart())
        {
            if (!bTimerStart)
            {
                bTimerStart = true;
                MD_LOG(Warning, TEXT("Call Start"));
                UpdateTimerDisplay();
                GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AMainCamera::AdvanceTimer, 1.0f, true);
            }
        }
        else
        {
            if (!MilDalGameManager().GetIsGameEnd())
            {
                CurrentLocation.X += MoveSpeed * DeltaTime;
                SetActorLocation(CurrentLocation);
                MoveSpeed = 20.0f;
            }
        }
    }
}

void AMainCamera::Notify()
{
    MD_LOG(Warning, TEXT("AMainCamera Receive GameEnd"));
    CameraText->SetText(TEXT("Game End!"));
    CameraText->MoveComponent(FVector(0.0f, 0.0f, 200.0f), FRotator(0.0f, 180.0f, 0.0f), false);
    CameraText->SetVisibility(true);
    MoveSpeed = 0.0f;
}

void AMainCamera::UpdateTimerDisplay()
{
    CameraText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void AMainCamera::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();

    if (CountdownTime < 1)
    {
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void AMainCamera::CountdownHasFinished()
{
    CameraText->SetText(TEXT("GO!"));
    MilDalGameManager().SetIsGameStart(true);
    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, FTimerDelegate::CreateLambda([&]()
        {
            CameraText->SetVisibility(false);
        }), 1.0f, false);
}
