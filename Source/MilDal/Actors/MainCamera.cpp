#include "MainCamera.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"

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

    Tags.Add("Camera");
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
}

void AMainCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    CurrentLocation.X += MoveSpeed * DeltaTime;
    SetActorLocation(CurrentLocation);

    if (MilDalGameManager().GetPlayerOneIsReady() && MilDalGameManager().GetPlayerTwoIsReady())
    {
        MoveSpeed = 20.0f;
    }
}