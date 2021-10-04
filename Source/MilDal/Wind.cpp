#include "Wind.h"
#include "WindObstacle.h"

AWind::AWind()
{
    PrimaryActorTick.bCanEverTick = true;
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> WindModel(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

    if (WindModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(WindModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
        StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    RootComponent = StaticMeshComp;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleHalfHeight(60.0f);
    CapsuleComponent->SetCapsuleRadius(60.0f);
    CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    CapsuleComponent->SetupAttachment(RootComponent);

    PitchValue = 0.f;
    YawValue = 1.f;
    RollValue = 0.f;

}

// Called when the game starts or when spawned
void AWind::BeginPlay()
{
    Super::BeginPlay();
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AWind::OnBeginOverlap);
}

void AWind::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AWind::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Player1P") || OtherActor->ActorHasTag("Player2P"))
    {
        FTransform SpawnLocation;
        SpawnLocation.SetLocation(GetActorLocation());
        GetWorld()->SpawnActor<AWindObstacle>(AWindObstacle::StaticClass(), SpawnLocation);
        this->Destroy();
    }
}

