#include "MilDalPlayerController.h"
#include "MilDal/UI/MainWidget.h"
#include "MilDal/UI/PauseMenu.h"

AMilDalPlayerController::AMilDalPlayerController()
{
    static ConstructorHelpers::FClassFinder<UMainWidget> MainHUD(TEXT("WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
    if (MainHUD.Succeeded())
    {
        HudWidgetClass = MainHUD.Class;
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

    MainWidget = CreateWidget<UMainWidget>(this, HudWidgetClass);
    MainWidget->AddToViewport(1);
}

void AMilDalPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction(TEXT("Pause"), EInputEvent::IE_Pressed, this, &AMilDalPlayerController::OnGamePause);
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