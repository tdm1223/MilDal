#include "MilDal/Player/UIPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MilDal/UI/TitleMenu.h"

AUIPlayerController::AUIPlayerController()
{
    static ConstructorHelpers::FClassFinder<UTitleMenu> TitleHUD(TEXT("WidgetBlueprint'/Game/Blueprints/BP_TitleMenu.BP_TitleMenu_C'"));
    if (TitleHUD.Succeeded())
    {
        UITitleClass = TitleHUD.Class;
    }
}

void AUIPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UITitleInstance = CreateWidget<UTitleMenu>(this, UITitleClass);
    UITitleInstance->AddToViewport();

    FInputModeUIOnly Mode;
    Mode.SetWidgetToFocus(UITitleInstance->GetCachedWidget());

    SetInputMode(Mode);
    bShowMouseCursor = true;
}
