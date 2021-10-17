#include "MilDal/MilDal.h"
#include "MilDal/UI/TitleMenu.h"

#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleMenu::NativeConstruct()
{
    Super::NativeConstruct();
    Start = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
    Option = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));
    Quit = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));

    if (Start)
    {
        Start->OnClicked.AddDynamic(this, &UTitleMenu::OnStart);
    }
    if (Option)
    {
        Option->OnClicked.AddDynamic(this, &UTitleMenu::OnOption);
    }
    if (Quit)
    {
        Quit->OnClicked.AddDynamic(this, &UTitleMenu::OnQuit);
    }
}

void UTitleMenu::OnStart()
{
    UGameplayStatics::OpenLevel(this, TEXT("Main"), false, TEXT("?Game=/Script/MilDal.MilDalGameModeBase"));
}

void UTitleMenu::OnOption()
{
    MD_LOG(Warning, TEXT("OptionClick"));
}

void UTitleMenu::OnQuit()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}