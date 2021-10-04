#include "Helicopter.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"

AHelicopter::AHelicopter()
{
    PrimaryActorTick.bCanEverTick = true;

    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ATestPawnArrowComponent"));
    RootComponent = Arrow;

    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    Motor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Motor"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyModel(TEXT("StaticMesh'/Game/Prop/Meshes/Helicopter.Helicopter'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MotorModel(TEXT("StaticMesh'/Game/Prop/Meshes/Helicopter_rotator.Helicopter_rotator'"));
    if (BodyModel.Succeeded())
    {
        Body->SetStaticMesh(BodyModel.Object);
        Body->SetWorldScale3D(FVector(7.0f, 7.0f, 7.0f));
        Body->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }

    if (MotorModel.Succeeded())
    {
        Motor->SetStaticMesh(MotorModel.Object);
        Motor->SetWorldScale3D(FVector(7.0f, 7.0f, 7.0f));
        Motor->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    Body->SetupAttachment(RootComponent);
    Motor->SetupAttachment(RootComponent);

    YawValue = 15.f;
}


void AHelicopter::BeginPlay()
{
    Super::BeginPlay();
}

void AHelicopter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FQuat QuatRotation = FQuat(FRotator(0.0f, YawValue, 0.0f));
    Motor->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);

    int dir = 1;
    if (this->GetActorRotation().Yaw != 0)
    {
        dir *= -1;
    }

    MotorLocation.Y -= MoveSpeed * DeltaTime * dir;
    Motor->AddWorldOffset(MotorLocation);

    BodyLocation.Y -= MoveSpeed * DeltaTime * dir;
    Body->AddWorldOffset(BodyLocation);
}