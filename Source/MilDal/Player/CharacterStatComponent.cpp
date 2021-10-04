#include "CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MilDal/Manager/MilDalGameInstance.h"
#include "MilDal/UI/MainWidget.h"

UCharacterStatComponent::UCharacterStatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
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
    if (this->GetOwner()->ActorHasTag("Player2P"))
    {
        MilDalGameManager().GetMainwWidget()->SetPlayerTwoLifeText(Life);
    }
    else
    {
        MilDalGameManager().GetMainwWidget()->SetPlayerOneLifeText(Life);
    }
}

void UCharacterStatComponent::IncreaseLife()
{
    Life++;
}

void UCharacterStatComponent::DecreaseLife()
{
    Life--;
}
