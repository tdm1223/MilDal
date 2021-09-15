#include "MilDalGameManager.h"
#include "Kismet/GameplayStatics.h"

UMilDalGameManager::UMilDalGameManager()
{
    FindClassType = AMainCamera::StaticClass();

    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), FindClassType, actors);

    for (auto actor : actors)
    {
        MainCamera = Cast<AMainCamera>(actor);
    }
}

FVector UMilDalGameManager::GetCameraInfo()
{
    UE_LOG(LogTemp, Log, TEXT("GetCameraInfo : %f %f %f"), MainCamera->GetActorLocation().X, MainCamera->GetActorLocation().Y, MainCamera->GetActorLocation().Z);

    return MainCamera->GetActorLocation();
}
