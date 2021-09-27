#include "MilDalPlayerController.h"
#include "MainWidget.h"

AMilDalPlayerController::AMilDalPlayerController()
{
    static ConstructorHelpers::FClassFinder<UMainWidget> HUD(TEXT("WidgetBlueprint'/Game/Blueprints/MainWidget.MainWidget_C'"));
    if (HUD.Succeeded())
    {
        HudWidgetClass = HUD.Class;
    }
}

void AMilDalPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());

    HudWidget = CreateWidget<UMainWidget>(this, HudWidgetClass);
    HudWidget->AddToViewport(1);
}