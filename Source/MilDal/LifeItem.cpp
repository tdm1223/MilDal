#include "LifeItem.h"

ALifeItem::ALifeItem()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> LifeModel(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

    if (LifeModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(LifeModel.Object);
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
    }
    else if(OtherActor->ActorHasTag("Player2P"))
    {
        Cast<AMilDalPlayer>(OtherActor)->IncreaseLife();
    }
    this->Destroy();
}