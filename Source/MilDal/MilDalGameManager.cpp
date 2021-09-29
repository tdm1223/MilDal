#include "MilDalGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "MilDalPlayerController.h"
#include "MilDalPlayer.h"
#include "MainCamera.h"
#include "MainWidget.h"

UMilDalGameManager::UMilDalGameManager()
{
    FindClassType = AMainCamera::StaticClass();

    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), FindClassType, actors);

    for (auto actor : actors)
    {
        UE_LOG(LogTemp, Log, TEXT("%s"), *actor->GetName());
        MainCamera = Cast<AMainCamera>(actor);
    }
}

FVector UMilDalGameManager::GetCameraInfo()
{
    UE_LOG(LogTemp, Log, TEXT("GetCameraInfo : %f %f %f"), MainCamera->GetActorLocation().X, MainCamera->GetActorLocation().Y, MainCamera->GetActorLocation().Z);

    return MainCamera->GetActorLocation();
}

void UMilDalGameManager::SetReverse(bool bReverse, bool bIsPlayerOne)
{
    if (bIsPlayerOne)
    {
        PlayerTwo->SetReverse(bReverse);
    }
    else
    {
        PlayerOne->SetReverse(bReverse);
    }
}

void UMilDalGameManager::RegisterPlayer(AMilDalPlayer* player, bool bIsPlayerOne)
{
    if (bIsPlayerOne)
    {
        PlayerOne = player;
    }
    else
    {
        PlayerTwo = player;
    }
}

void UMilDalGameManager::RegisterController()
{
    controller = Cast<AMilDalPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    MainWidget = controller->GetMainWidget();
}

UMainWidget* UMilDalGameManager::GetMainwWidget() const
{
    return MainWidget;
}
