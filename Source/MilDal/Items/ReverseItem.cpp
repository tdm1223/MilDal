#include "ReverseItem.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"

AReverseItem::AReverseItem()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ReverseModel(TEXT("StaticMesh'/Game/Prop/Meshes/Reverse.Reverse'"));
    if (ReverseModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(ReverseModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
        StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    RootComponent = StaticMeshComp;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleRadius(15.0f);
    CapsuleComponent->SetCapsuleHalfHeight(15.0f);
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
        MilDalGameManager().SetReverse(true, PlayerType::PlayerOne);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetReverse(false, PlayerType::PlayerOne);
            }), ReverseTime, false);
        this->Destroy();
    }
    else if(OtherActor->ActorHasTag("Player2P"))
    {
        MilDalGameManager().SetReverse(true, PlayerType::PlayerTwo);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetReverse(false, PlayerType::PlayerTwo);
            }), ReverseTime, false);
        this->Destroy();

    }
}