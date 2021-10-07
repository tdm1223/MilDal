#include "MilDal/UI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    //Start = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
    //Option = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));
    //Quit = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));

    //Start->OnClicked.AddDynamic(this, &UMainMenu::OnStart);
    //Option->OnClicked.AddDynamic(this, &UMainMenu::OnOption);
    //Quit->OnClicked.AddDynamic(this, &UMainMenu::OnQuit);
}

void UMainMenu::OnStart()
{
    UE_LOG(LogTemp, Log, TEXT("ClickStart"));
}

void UMainMenu::OnOption()
{
    UE_LOG(LogTemp, Log, TEXT("ClickStart"));
}

void UMainMenu::OnQuit()
{
    UE_LOG(LogTemp, Log, TEXT("ClickStart"));
}