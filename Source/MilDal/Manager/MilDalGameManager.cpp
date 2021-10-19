#include "MilDalGameManager.h"
#include "MilDal/Actors/MainCamera.h"
#include "MilDal/Manager/MilDalGameModeBase.h"
#include "MilDal/Player/MilDalPlayerController.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "MilDal/UI/MainWidget.h"

#include "Kismet/GameplayStatics.h"

UMilDalGameManager::UMilDalGameManager()
{
    FindClassType = AMainCamera::StaticClass();
    bPlayerOneIsReady = false;
    bPlayerTwoIsReady = false;
    bIsGameEnd = false;
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
    for (TObjectIterator<AMainCamera> It; It; ++It)
    {
        MainCamera = *It;
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

    mode = Cast<AMilDalGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

UMainWidget* UMilDalGameManager::GetMainwWidget() const
{
    return MainWidget;
}

void UMilDalGameManager::NotifyGameOver()
{
    bIsGameEnd = true;
    GameEndDelegate.Broadcast();
}