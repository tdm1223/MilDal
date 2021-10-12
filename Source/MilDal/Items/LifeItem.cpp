#include "LifeItem.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "Kismet/GameplayStatics.h"

ALifeItem::ALifeItem()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> LifeModel(TEXT("StaticMesh'/Game/Prop/Meshes/Life.Life'"));

    if (LifeModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(LifeModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
        StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    RootComponent = StaticMeshComp;
    StaticMeshComp->CastShadow = false;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleHalfHeight(60.0f);
    CapsuleComponent->SetCapsuleRadius(60.0f);
    CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
    CapsuleComponent->SetupAttachment(RootComponent);

    PitchValue = 0.f;
    YawValue = 1.f;
    RollValue = 0.f;

    PlaneComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneModel(TEXT("StaticMesh'/Engine/BasicShapes/RedPlane.RedPlane'"));
    if (PlaneModel.Succeeded())
    {
        PlaneComp->SetStaticMesh(PlaneModel.Object);
        PlaneComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
        PlaneComp->SetRelativeLocation(FVector(0.0f, 0.0f, -235.0f));
    }
    PlaneComp->SetupAttachment(RootComponent);
}

void ALifeItem::BeginPlay()
{
    Super::BeginPlay();

    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ALifeItem::OnBeginOverlap);
}

void ALifeItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));

    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ALifeItem::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Player1P"))
    {
        Cast<AMilDalPlayer>(OtherActor)->IncreaseLife();
        this->Destroy();
    }
    else if(OtherActor->ActorHasTag("Player2P"))
    {
        Cast<AMilDalPlayer>(OtherActor)->IncreaseLife();
        this->Destroy();
    }
}