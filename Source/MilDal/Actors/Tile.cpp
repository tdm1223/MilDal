#include "Tile.h"
#include "GameFramework/Actor.h"

ATile::ATile()
{
    PrimaryActorTick.bCanEverTick = false;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> TileModel(TEXT("StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400'"));

    if (TileModel.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(TileModel.Object);
        StaticMeshComp->SetWorldScale3D(FVector(6.0, 2.0, 1.0));
    }
    RootComponent = StaticMeshComp;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
    Super::BeginPlay();
    StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlapBegin);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ATile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Camera"))
    {
        FVector location = GetActorLocation();
        location.X += 2400;
        GetWorld()->SpawnActor<ATile>(ATile::StaticClass(), location, FRotator::ZeroRotator);
    }
}