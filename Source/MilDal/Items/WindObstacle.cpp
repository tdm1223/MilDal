#include "WindObstacle.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"

AWindObstacle::AWindObstacle()
{
    PrimaryActorTick.bCanEverTick = true;

    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ATestPawnArrowComponent"));
    RootComponent = Arrow;

    LeftObstacle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftObstacle"));
    RightObstacle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightObstacle"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> WindModel(TEXT("StaticMesh'/Game/Prop/Meshes/Wind.Wind'"));

    LeftObstacle->SetupAttachment(RootComponent);
    RightObstacle->SetupAttachment(RootComponent);

    if (WindModel.Succeeded())
    {
        LeftObstacle->SetStaticMesh(WindModel.Object);
        LeftObstacle->SetWorldScale3D(FVector(1.5f, 2.5f, 5.5f));
        LeftObstacle->SetRelativeLocation(FVector(0.0f, -150.0f, 0.0f));

        RightObstacle->SetStaticMesh(WindModel.Object);
        RightObstacle->SetWorldScale3D(FVector(1.5f, 2.5f, 5.5f));
        RightObstacle->SetRelativeLocation(FVector(0.0f, 150.0f, 0.0f));
    }
}

void AWindObstacle::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle WaitHandle;
    GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        {
            this->Destroy();
        }), SpawnTime, false);
}

void AWindObstacle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    LeftLocation.Y -= MoveSpeed * DeltaTime;
    LeftObstacle->AddLocalOffset(LeftLocation);

    RightLocation.Y += MoveSpeed * DeltaTime;
    RightObstacle->AddLocalOffset(RightLocation);
}