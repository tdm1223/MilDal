#include "FastItem.h"
#include "Components/CapsuleComponent.h"
#include "MilDalGameInstance.h"

AFastItem::AFastItem()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    //static ConstructorHelpers::FObjectFinder<UStaticMesh> TileModel(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> TileModel(TEXT("StaticMesh'/Game/Prop/Meshes/Fan.Fan'"));

    if (TileModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(TileModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
        StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    RootComponent = StaticMeshComp;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleHalfHeight(90.0f);
    CapsuleComponent->SetCapsuleRadius(90.0f);
    CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    CapsuleComponent->SetupAttachment(RootComponent);

    PitchValue = 0.f;
    YawValue = 1.f;
    RollValue = 0.f;
}

void AFastItem::BeginPlay()
{
    Super::BeginPlay();
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AFastItem::OnBeginOverlap);
}

void AFastItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AFastItem::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    FTimerHandle WaitHandle;
    if (OtherActor->ActorHasTag("Player1P"))
    {
        MilDalGameManager().SetFast(true, PlayerType::PlayerOne);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetFast(false, PlayerType::PlayerOne);
            }), Duration, false);
        this->Destroy();
    }
    else if(OtherActor->ActorHasTag("Player2P"))
    {
        MilDalGameManager().SetFast(true, PlayerType::PlayerTwo);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetFast(false, PlayerType::PlayerTwo);
            }), Duration, false);
        this->Destroy();
    }
}

