#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"

AMainCamera::AMainCamera()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMainCamera::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        UE_LOG(LogTemp, Log, TEXT("Success"));
        PlayerController->SetViewTargetWithBlend(this);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Fail"));
    }

    CurrentLocation = this->GetActorLocation();
}

void AMainCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Log, TEXT("Tick"));
    CurrentLocation.X += MoveSpeed * DeltaTime; // use X Y or Z.  Use -= to go the opposite way
    SetActorLocation(CurrentLocation);
}