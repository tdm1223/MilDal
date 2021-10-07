#include "MilDalGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "MilDal/Player/MilDalPlayerController.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "MilDal/Actors/MainCamera.h"
#include "MilDal/UI/MainWidget.h"

UMilDalGameManager::UMilDalGameManager()
{
    FindClassType = AMainCamera::StaticClass();

    SetMainCamera();
}

FVector UMilDalGameManager::GetCameraInfo()
{
    if (MainCamera != nullptr)
    {
        return MainCamera->GetActorLocation();
    }
    else
    {
        SetMainCamera();
        return MainCamera->GetActorLocation();
    }
}

void UMilDalGameManager::SetMainCamera()
{
    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), FindClassType, actors);
    for (auto actor : actors)
    {
        MainCamera = Cast<AMainCamera>(actor);
    }
}

void UMilDalGameManager::SetReverse(bool bReverse, PlayerType InEatPlayer)
{
    if (InEatPlayer == PlayerType::PlayerOne)
    {
        PlayerTwo->SetReverse(bReverse);
    }
    else if (InEatPlayer == PlayerType::PlayerTwo)
    {
        PlayerOne->SetReverse(bReverse);
    }
}

void UMilDalGameManager::SetInfiniteJump(bool bJump, PlayerType InEatPlayer)
{
    if (InEatPlayer == PlayerType::PlayerOne)
    {
        PlayerOne->SetInfiniteJump(bJump);
    }
    else if (InEatPlayer == PlayerType::PlayerTwo)
    {
        PlayerTwo->SetInfiniteJump(bJump);
    }
}

void UMilDalGameManager::SetFast(bool bFast, PlayerType InEatPlayer)
{
    if (InEatPlayer == PlayerType::PlayerOne)
    {
        PlayerTwo->SetFast(bFast);
    }
    else if (InEatPlayer == PlayerType::PlayerTwo)
    {
        PlayerOne->SetFast(bFast);
    }
}

void UMilDalGameManager::RegistPlayer(AMilDalPlayer* player, PlayerType InCurrentPlayer)
{
    if (InCurrentPlayer == PlayerType::PlayerOne)
    {
        PlayerOne = player;
    }
    else if (InCurrentPlayer == PlayerType::PlayerTwo)
    {
        PlayerTwo = player;
    }
}

void UMilDalGameManager::RegistController()
{
    controller = Cast<AMilDalPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    MainWidget = controller->GetMainWidget();
}

UMainWidget* UMilDalGameManager::GetMainwWidget() const
{
    return MainWidget;
}
