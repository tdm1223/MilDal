#include "MainWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/Player/MilDalPlayer.h"
#include "MilDal/Player/CharacterStatComponent.h"
#include "MilDal/UI/LifePanel.h"

void UMainWidget::NativeConstruct()
{
    Super::NativeConstruct();
    PlayerOneLifePanel = Cast<ULifePanel>(GetWidgetFromName(TEXT("PlayerOneLife")));
    PlayerTwoLifePanel = Cast<ULifePanel>(GetWidgetFromName(TEXT("PlayerTwoLife")));
}

void UMainWidget::SetPlayerOneLife(int InLife)
{
    for (int i = 0; i < 5; i++)
    {
        PlayerOneLifePanel->LifeArray[i]->SetVisibility(ESlateVisibility::Hidden);
    }
    for (int i = 0; i < InLife; i++)
    {
        PlayerOneLifePanel->LifeArray[i]->SetVisibility(ESlateVisibility::Visible);
    }
}

void UMainWidget::SetPlayerTwoLife(int InLife)
{
    for (int i = 0; i < 5; i++)
    {
        PlayerTwoLifePanel->LifeArray[i]->SetVisibility(ESlateVisibility::Hidden);
    }
    for (int i = 0; i < InLife; i++)
    {
        PlayerTwoLifePanel->LifeArray[4 - i]->SetVisibility(ESlateVisibility::Visible);
    }
}