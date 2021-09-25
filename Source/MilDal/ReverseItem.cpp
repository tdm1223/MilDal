#include "ReverseItem.h"

AReverseItem::AReverseItem()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> TileModel(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

    if (TileModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(TileModel.Object);
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

void AReverseItem::BeginPlay()
{
    Super::BeginPlay();
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AReverseItem::OnBeginOverlap);
}

void AReverseItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AReverseItem::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    FTimerHandle WaitHandle;
    if (OtherActor->ActorHasTag("Player1P"))
    {
        MilDalGameManager().SetReverse(true, true);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetReverse(false, true);
            }), ReverseTime, false);
    }
    else
    {
        MilDalGameManager().SetReverse(true, false);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetReverse(false, false);
            }), ReverseTime, false);
    }
    this->Destroy();
}