#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"

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

    // 생성자가 아닌 BeginPlay에 추가해줘야 한다.
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMainCamera::OnOverlapBegin);
}

void AMainCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    CurrentLocation.X += MoveSpeed * DeltaTime;
    SetActorLocation(CurrentLocation);
}

void AMainCamera::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        UE_LOG(LogTemp, Log, TEXT("Collision Detect"));
    }
}
