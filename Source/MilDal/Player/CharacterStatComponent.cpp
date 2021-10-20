#include "CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/UI/MainWidget.h"

UCharacterStatComponent::UCharacterStatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    Life = 3;
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
    SetLifePanel();
}

void UCharacterStatComponent::IncreaseLife()
{
    if (Life < 5)
    {
        Life++;
    }
}

void UCharacterStatComponent::DecreaseLife()
{
    if (Life > 0)
    {
        Life--;
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
