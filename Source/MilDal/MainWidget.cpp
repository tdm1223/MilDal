#include "MainWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "MilDalGameInstance.h"
#include "MilDalPlayer.h"
#include "CharacterStatComponent.h"

void UMainWidget::NativeConstruct()
{
    Super::NativeConstruct();
    PlayerOneLifePanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("PlayerOneLife")));
    PlayerTwoLifePanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("PlayerTwoLife")));
    PlayerOneLifeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerOneLifeT")));
    PlayerTwoLifeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerTwoLifeT")));
}

void UMainWidget::SetPlayerOneLifeText(int InLife)
{
    PlayerOneLifeText->SetText(FText::FromString(FString::FromInt(InLife)));
}

void UMainWidget::SetPlayerTwoLifeText(int InLife)
{
    PlayerTwoLifeText->SetText(FText::FromString(FString::FromInt(InLife)));
}