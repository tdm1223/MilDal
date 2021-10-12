#include "WindItem.h"
#include "WindObstacle.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

AWindItem::AWindItem()
{
    PrimaryActorTick.bCanEverTick = true;
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> WindModel(TEXT("StaticMesh'/Game/Prop/Meshes/Wind.Wind'"));

    if (WindModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(WindModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
        StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    RootComponent = StaticMeshComp;
    StaticMeshComp->CastShadow = false;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleHalfHeight(30.0f);
    CapsuleComponent->SetCapsuleRadius(30.0f);
    CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    CapsuleComponent->SetupAttachment(RootComponent);

    PitchValue = 0.f;
    YawValue = 1.f;
    RollValue = 0.f;

    PlaneComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneModel(TEXT("StaticMesh'/Engine/BasicShapes/RedPlane.RedPlane'"));
    if (PlaneModel.Succeeded())
    {
        PlaneComp->SetStaticMesh(PlaneModel.Object);
        PlaneComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
        PlaneComp->SetRelativeLocation(FVector(0.0f, 0.0f, -115.0f));
    }
    PlaneComp->SetupAttachment(RootComponent);
}

void AWindItem::BeginPlay()
{
    Super::BeginPlay();
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AWindItem::OnBeginOverlap);
}

void AWindItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AWindItem::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Player1P") || OtherActor->ActorHasTag("Player2P"))
    {
        FTransform SpawnLocation;
        SpawnLocation.SetLocation(GetActorLocation());
        GetWorld()->SpawnActor<AWindObstacle>(AWindObstacle::StaticClass(), SpawnLocation);
        this->Destroy();
    }
}

