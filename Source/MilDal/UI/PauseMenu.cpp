#include "MilDal/UI/PauseMenu.h"
#include "MilDal/Player/MilDalPlayerController.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/Manager/MilDalGameModeBase.h"

#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenu::NativeConstruct()
{
    Super::NativeConstruct();
    Resume = Cast<UButton>(GetWidgetFromName(TEXT("ResumeButton")));
    if (Resume)
    {
        Resume->OnClicked.AddDynamic(this, &UPauseMenu::OnResume);
    }

    Title = Cast<UButton>(GetWidgetFromName(TEXT("TitleButton")));
    if (Title)
    {
        Title->OnClicked.AddDynamic(this, &UPauseMenu::OnTitle);
    }

    Quit = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
    if (Quit)
    {
        Quit->OnClicked.AddDynamic(this, &UPauseMenu::OnQuit);
    }
}

void UPauseMenu::OnResume()
{
    auto controller = Cast<AMilDalPlayerController>(GetOwningPlayer());
    RemoveFromParent();
    controller->ChangeInputMode(true);
    controller->SetPause(false);
}

void UPauseMenu::OnTitle()
{
    mode = Cast<AMilDalGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    mode->ClearTimer();

    MilDalGameManager().SetPlayerOneIsReady(false);
    MilDalGameManager().SetPlayerTwoIsReady(false);
    UGameplayStatics::OpenLevel(this, TEXT("Title"), false, TEXT("?Game=/Script/MilDal.TitleGameMode"));
}

void UPauseMenu::OnQuit()
{
    UE_LOG(LogTemp, Log, TEXT("ClickStart"));
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}