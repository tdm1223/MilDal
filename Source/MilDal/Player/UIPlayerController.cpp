#include "MilDal/Player/UIPlayerController.h"
#include "Blueprint/UserWidget.h"

void AUIPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);

    UIWidgetInstance->AddToViewport();

    FInputModeUIOnly Mode;
    Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());

    SetInputMode(Mode);
    bShowMouseCursor = true;
}
