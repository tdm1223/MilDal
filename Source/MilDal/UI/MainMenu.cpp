#include "MilDal/UI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    Start = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
    //Option = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));
    Quit = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));

    if (Start)
    {
        Start->OnClicked.AddDynamic(this, &UMainMenu::OnStart);
    }
    //Option->OnClicked.AddDynamic(this, &UMainMenu::OnOption);
    if (Quit)
    {
        Quit->OnClicked.AddDynamic(this, &UMainMenu::OnQuit);
    }
}

void UMainMenu::OnStart()
{
    UGameplayStatics::OpenLevel(this, TEXT("Main"));
}

void UMainMenu::OnOption()
{
    UE_LOG(LogTemp, Log, TEXT("OptionClick"));
}

void UMainMenu::OnQuit()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}