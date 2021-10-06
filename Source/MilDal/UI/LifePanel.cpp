#include "MilDal/UI/LifePanel.h"
#include "Components/Image.h"

void ULifePanel::NativeConstruct()
{
    Super::NativeConstruct();
    LifeOne = Cast<UImage>(GetWidgetFromName(TEXT("Life1")));
    LifeTwo = Cast<UImage>(GetWidgetFromName(TEXT("Life2")));
    LifeThree = Cast<UImage>(GetWidgetFromName(TEXT("Life3")));
    LifeFour = Cast<UImage>(GetWidgetFromName(TEXT("Life4")));
    LifeFive = Cast<UImage>(GetWidgetFromName(TEXT("Life5")));

    LifeArray.Add(LifeOne);
    LifeArray.Add(LifeTwo);
    LifeArray.Add(LifeThree);
    LifeArray.Add(LifeFour);
    LifeArray.Add(LifeFive);
}