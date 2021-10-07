#include "CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/UI/MainWidget.h"

UCharacterStatComponent::UCharacterStatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    Life = 5;
    Speed = 200.0f;
}

void UCharacterStatComponent::BeginPlay()
{
    Super::BeginPlay();

    if (this->GetOwner()->ActorHasTag("Player2P"))
    {
        Name = TEXT("2P");
    }
    else
    {
        Name = TEXT("1P");
    }
}

void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterStatComponent::IncreaseLife()
{
    if (Life < 5)
    {
        Life++;
        SetLifePanel();
    }
}

void UCharacterStatComponent::DecreaseLife()
{
    if (Life > 0)
    {
        Life--;
        SetLifePanel();
    }
}

void UCharacterStatComponent::SetLifePanel()
{
    if (this->GetOwner()->ActorHasTag("Player2P"))
    {
        MilDalGameManager().GetMainwWidget()->SetPlayerTwoLife(Life);
    }
    else if ((this->GetOwner()->ActorHasTag("Player1P")))
    {
        MilDalGameManager().GetMainwWidget()->SetPlayerOneLife(Life);
    }
}
