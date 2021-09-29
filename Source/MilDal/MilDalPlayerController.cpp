#include "MilDalPlayerController.h"
#include "MainWidget.h"

AMilDalPlayerController::AMilDalPlayerController()
{
    static ConstructorHelpers::FClassFinder<UMainWidget> HUD(TEXT("WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
    if (HUD.Succeeded())
    {
        HudWidgetClass = HUD.Class;
    }
}

void AMilDalPlayerController::BeginPlay()
{
    Super::BeginPlay();
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);

    MainWidget = CreateWidget<UMainWidget>(this, HudWidgetClass);
    MainWidget->AddToViewport(1);
}

UMainWidget* AMilDalPlayerController::GetMainWidget() const
{
    return MainWidget;
}