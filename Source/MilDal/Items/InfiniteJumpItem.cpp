#include "InfiniteJumpItem.h"
#include "Components/CapsuleComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "GameFramework/Actor.h"

AInfiniteJumpItem::AInfiniteJumpItem()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    //static ConstructorHelpers::FObjectFinder<UStaticMesh> TileModel(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> TileModel(TEXT("StaticMesh'/Game/Prop/Meshes/InfiniteJump.InfiniteJump'"));

    if (TileModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(TileModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
        StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    RootComponent = StaticMeshComp;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleHalfHeight(10.0f);
    CapsuleComponent->SetCapsuleRadius(10.0f);
    CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    CapsuleComponent->SetupAttachment(RootComponent);

    PitchValue = 0.f;
    YawValue = 1.f;
    RollValue = 0.f;
}

void AInfiniteJumpItem::BeginPlay()
{
    Super::BeginPlay();
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AInfiniteJumpItem::OnBeginOverlap);
}

void AInfiniteJumpItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AInfiniteJumpItem::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    FTimerHandle WaitHandle;
    if (OtherActor->ActorHasTag("Player1P"))
    {
        MilDalGameManager().SetInfiniteJump(true, PlayerType::PlayerOne);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetInfiniteJump(false, PlayerType::PlayerOne);
            }), ItemTime, false);
        this->Destroy();
    }
    else if(OtherActor->ActorHasTag("Player2P"))
    {
        MilDalGameManager().SetInfiniteJump(true, PlayerType::PlayerTwo);
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
            {
                MilDalGameManager().SetInfiniteJump(false, PlayerType::PlayerTwo);
            }), ItemTime, false);
        this->Destroy();
    }
}

