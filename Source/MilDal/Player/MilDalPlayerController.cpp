#include "MilDalPlayerController.h"

#include "MilDal/UI/MainWidget.h"
#include "MilDal/UI/PauseMenu.h"

#include "MilDal/Manager/MilDalGameModeBase.h"
#include "MilDal/Manager/MilDalGameInstance.h"

#include "Kismet/GameplayStatics.h"

AMilDalPlayerController::AMilDalPlayerController()
{
    static ConstructorHelpers::FClassFinder<UMainWidget> MainHUD(TEXT("WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
    if (MainHUD.Succeeded())
    {
        MainWidgetClass = MainHUD.Class;
    }

    static ConstructorHelpers::FClassFinder<UPauseMenu> PauseHUD(TEXT("WidgetBlueprint'/Game/Blueprints/BP_PauseMenu.BP_PauseMenu_C'"));
    if (PauseHUD.Succeeded())
    {
        PauseWidgetClass = PauseHUD.Class;
    }
}

void AMilDalPlayerController::BeginPlay()
{
    Super::BeginPlay();
    ChangeInputMode(true);

    MainWidget = CreateWidget<UMainWidget>(this, MainWidgetClass);
    MainWidget->AddToViewport(1);
}

void AMilDalPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction(TEXT("Pause"), EInputEvent::IE_Pressed, this, &AMilDalPlayerController::OnGamePause);
    InputComponent->BindAction(TEXT("Restart"), EInputEvent::IE_Pressed, this, &AMilDalPlayerController::OnGameRestart);
}

UMainWidget* AMilDalPlayerController::GetMainWidget() const
{
    return MainWidget;
}

void AMilDalPlayerController::ChangeInputMode(bool bGameMode)
{
    if (bGameMode)
    {
        SetInputMode(GameInputMode);
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(UIInputMode);
        bShowMouseCursor = true;
    }
}

void AMilDalPlayerController::OnGamePause()
{
    PauseWidget = CreateWidget<UPauseMenu>(this, PauseWidgetClass);
    PauseWidget->AddToViewport(3);
    SetPause(true);
    ChangeInputMode(false);
}

void AMilDalPlayerController::OnGameRestart()
{
    mode = Cast<AMilDalGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    mode->ClearTimer();

    MilDalGameManager().SetPlayerOneIsReady(false);
    MilDalGameManager().SetPlayerTwoIsReady(false);
    UGameplayStatics::OpenLevel(this, TEXT("Main"), false, TEXT("?Game=/Script/MilDal.MilDalGameModeBase"));
}